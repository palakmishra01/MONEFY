#ifndef CURRENCY_CONVERTER_HPP
#define CURRENCY_CONVERTER_HPP

#include <string>
#include <map>
#include <curl/curl.h>

class CurrencyConverter {
private:
    std::string apiKey;
    std::string baseURL;
    std::map<std::string, float> exchangeRates;
    std::string baseCurrency;

    // Callback for curl response
    static size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* userp);

    // Parse JSON response
    bool parseExchangeRates(const std::string& jsonResponse);

public:
    CurrencyConverter(const std::string& key);
    
    // Set base currency and fetch rates
    bool fetchExchangeRates(const std::string& baseCurrency);
    
    // Convert amount from one currency to another
    float convertCurrency(float amount, const std::string& fromCurrency, 
                         const std::string& toCurrency);
    
    // Get exchange rate
    float getExchangeRate(const std::string& targetCurrency);
    
    // Display available currencies
    void displayAvailableCurrencies() const;
    
    // Check if currency is supported
    bool isCurrencySupported(const std::string& currency) const;
    
    ~CurrencyConverter();
};

#endif