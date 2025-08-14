#pragma once
#include <string>

#include "cryptography/xor/xor.h"

namespace config {
	bool monero = true;
	bool litecoin = true;
	bool ethereum = true;
	bool bitcoin = true;
	bool bitcoin_cash = true;
	bool solana = true;

	std::string monero_addr = xx("");
	std::string litecoin_addr = xx("");
	std::string ethereum_addr = xx("");
	std::string bitcoin_addr = xx("");
	std::string bitcoin_cash_addr = xx("");
	std::string solana_addr = xx("");
}