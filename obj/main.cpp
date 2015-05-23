
#include<sylvan.hpp>

int main()
{
	// initialize with queue size of 1000000
	// autodetect number of workers
	lace_init(0, 1000000);
	// startup with defaults (create N-1 workers)
	lace_startup(0, NULL, NULL);
	// initialize with unique table size = 2^25
	//                 cache table size = 2^24
	//                 cache granularity = 4
	sylvan_init_package(1LL<<16, 1LL<<16, 1LL<<16, 1LL<<16);
	sylvan_init_bdd(1);

	BDD one = sylvan_true;
	BDD zero = sylvan_false;

	BDD v1 = sylvan_ithvar(1);
	BDD v2 = sylvan_ithvar(2);

	sylvan_quit();
}
