#include "spdlog/spdlog.h"
#include "service.h"

int main() {
	auto console = spdlog::stdout_color_mt("XZeroConf");
	console->info("hellow world");

	xzc::Service service("service","");
	service.GetName();

	return 0;
}
