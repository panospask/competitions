#include "coreputer.h"

std::vector<int> malfunctioning_cores(int N) {
	int v = run_diagnostic({0});
	std::vector<int> ans(2, 0);

	if (v != -1)
		ans[0] = 1;
	if (v != 1)
		ans[1] = 1;

	return ans;
}
