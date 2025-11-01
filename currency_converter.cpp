#include "currency_converter.hpp"
#include <iostream>
#include <iomanip>
#include <map>
#include <string>

// For Windows, we'll use a simple JSON parsing approach
// If nlohmann/json is not available
#include <sstream>

// Callback function for CURL to handle response
size_t CurrencyConverter::WriteCallback(void* contents, size_t size, size_t nmemb, std::string* userp) {
    userp->append((char*)contents, size * nmemb);
    return size * nmemb;
}

CurrencyConverter::CurrencyConverter(const std::string& key)
    : apiKey(key), baseURL("https://api.exchangerate-api.com/v4/latest/"), baseCurrency("INR") {
    // Initialize with common currencies
}

bool CurrencyConverter::fetchExchangeRates(const std::string& baseCurrency) {
    CURL* curl = curl_easy_init();
    if (!curl) {
        std::cerr << "Error: Failed to initialize CURL" << std::endl;
        return false;
    }

    std::string url = baseURL + baseCurrency;
    std::string readBuffer;

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10L);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

    // For Windows SSL support
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1L);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 2L);

    CURLcode res = curl_easy_perform(curl);

    if (res != CURLE_OK) {
        std::cerr << "Error: Failed to fetch exchange rates: " 
                  << curl_easy_strerror(res) << std::endl;
        curl_easy_cleanup(curl);
        return false;
    }

    curl_easy_cleanup(curl);
    this->baseCurrency = baseCurrency;

    return parseExchangeRates(readBuffer);
}

// Simple JSON parser for extracting rates
bool CurrencyConverter::parseExchangeRates(const std::string& jsonResponse) {
    try {
        // Simple parsing: find "rates" section
        size_t ratesPos = jsonResponse.find("\"rates\"");
        if (ratesPos == std::string::npos) {
            std::cerr << "Error: Invalid API response format" << std::endl;
            return false;
        }

        exchangeRates.clear();

        // Extract rates from JSON
        size_t startPos = jsonResponse.find('{', ratesPos);
        size_t endPos = jsonResponse.find('}', startPos);

        if (startPos == std::string::npos || endPos == std::string::npos) {
            std::cerr << "Error: Could not parse rates" << std::endl;
            return false;
        }

        std::string ratesStr = jsonResponse.substr(startPos, endPos - startPos + 1);

        // Parse each currency:rate pair
        size_t pos = 0;
        while ((pos = ratesStr.find("\"", pos)) != std::string::npos) {
            size_t start = pos + 1;
            size_t end = ratesStr.find("\"", start);
            if (end == std::string::npos) break;

            std::string currency = ratesStr.substr(start, end - start);
            pos = end + 1;

            // Skip ':'
            size_t colonPos = ratesStr.find(':', pos);
            if (colonPos == std::string::npos) break;

            // Extract rate value
            size_t rateStart = colonPos + 1;
            size_t commaPos = ratesStr.find(',', rateStart);
            size_t bracePos = ratesStr.find('}', rateStart);
            size_t rateEnd = (commaPos < bracePos) ? commaPos : bracePos;

            std::string rateStr = ratesStr.substr(rateStart, rateEnd - rateStart);
            
            // Trim whitespace
            rateStr.erase(0, rateStr.find_first_not_of(" \t\n\r"));
            rateStr.erase(rateStr.find_last_not_of(" \t\n\r") + 1);

            try {
                float rate = std::stof(rateStr);
                if (currency.length() == 3 && rate > 0) {
                    exchangeRates[currency] = rate;
                }
            } catch (...) {
                // Skip invalid rates
            }

            pos = rateEnd;
        }

        if (exchangeRates.empty()) {
            std::cerr << "Error: No rates parsed" << std::endl;
            return false;
        }

        std::cout << "Exchange rates fetched successfully" << std::endl;
        return true;
    } catch (const std::exception& e) {
        std::cerr << "Error parsing JSON: " << e.what() << std::endl;
        return false;
    }
}

float CurrencyConverter::convertCurrency(float amount, const std::string& fromCurrency, 
                                        const std::string& toCurrency) {
    if (fromCurrency == toCurrency) {
        return amount;
    }

    // If converting from base currency
    if (fromCurrency == baseCurrency) {
        if (exchangeRates.find(toCurrency) != exchangeRates.end()) {
            return amount * exchangeRates[toCurrency];
        }
    }
    // If converting to base currency
    else if (toCurrency == baseCurrency) {
        if (exchangeRates.find(fromCurrency) != exchangeRates.end()) {
            return amount / exchangeRates[fromCurrency];
        }
    }
    // Cross currency conversion
    else {
        if (exchangeRates.find(fromCurrency) != exchangeRates.end() &&
            exchangeRates.find(toCurrency) != exchangeRates.end()) {
            float toBase = amount / exchangeRates[fromCurrency];
            return toBase * exchangeRates[toCurrency];
        }
    }

    std::cerr << "Error: Currency conversion failed. Unsupported currency." << std::endl;
    return 0.0f;
}

float CurrencyConverter::getExchangeRate(const std::string& targetCurrency) {
    if (exchangeRates.find(targetCurrency) != exchangeRates.end()) {
        return exchangeRates[targetCurrency];
    }
    return 0.0f;
}

void CurrencyConverter::displayAvailableCurrencies() const {
    if (exchangeRates.empty()) {
        std::cout << "No currencies available. Fetch rates first." << std::endl;
        return;
    }

    std::cout << std::endl;
    std::cout << "Available Currencies (Exchange rates to " << baseCurrency << "):" << std::endl;
    std::cout << "================================================" << std::endl;
    
    int count = 0;
    for (const auto& [currency, rate] : exchangeRates) {
        std::cout << std::fixed << std::setprecision(4);
        std::cout << std::left << std::setw(6) << currency << " : " << rate << std::endl;
        count++;
        if (count % 8 == 0) std::cout << std::endl;
    }
    std::cout << "================================================" << std::endl;
    std::cout << std::endl;
}

bool CurrencyConverter::isCurrencySupported(const std::string& currency) const {
    return exchangeRates.find(currency) != exchangeRates.end();
}

CurrencyConverter::~CurrencyConverter() {
    exchangeRates.clear();
}