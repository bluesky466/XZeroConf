#include "spdlog/spdlog.h"

int main() {
	auto console = spdlog::stdout_color_mt("XZeroConf");
	console->info("hellow world");

	return 0;
}
