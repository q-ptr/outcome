
#include <fmt/core.h>
#include <qptr/status.hpp>
#include <qptr/outcome/version.hpp>


int main()
{
	qptr::status   s1;
	qptr::status   s2(qptr::status::BUSY);
	qptr::status   s3(qptr::status::INVALID_CALL, "the call is not valid in this context");
	qptr::status   s4(qptr::status::INVALID_ARG, "invalid argument : {}", 123);

	fmt::print("s1 = {}\n", s1);
	fmt::print("s2 = {}\n", s2);
	fmt::print("s3 = {}\n", s3);
	fmt::print("s4 = {}\n", s4);

	return 0;
}
