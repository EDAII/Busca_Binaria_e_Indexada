#include <bits/stdc++.h>
#include <sys/resource.h>
#include <sys/time.h>
#define ll long long
#define pb push_back

using namespace std;

void sequential_search (ll searched_element, vector <ll> x) {
	for (ll i = 0; i < x.size (); ++i) if (x[i] == searched_element) return;
}

void indexed_search (ll searched_element, vector <ll> x, ll range_jump) {
	ll i, j;
	for (i = range_jump; i < x.size(); i += range_jump)
		if (x[i] >= searched_element) break;

	for (j = i - range_jump; x[j] != searched_element; j++)
		if (j == i+1) return;

	return;
}

ll binary_search (vector <ll> x, ll left, ll right, ll searched_element) {
	while (left <= right) {
		ll mid = left + (right - left)/2;
		if (x[mid] == searched_element) return mid;
		if (x[mid] < searched_element) left = mid + 1;
		else right = mid - 1;
	}

	return 0;
}

double calc_time (const struct rusage *b, const struct rusage *a) {
    if (b == NULL || a == NULL)
        return 0;
    else
        return ((((a->ru_utime.tv_sec * 1000000 + a->ru_utime.tv_usec) -
                 (b->ru_utime.tv_sec * 1000000 + b->ru_utime.tv_usec)) +
                ((a->ru_stime.tv_sec * 1000000 + a->ru_stime.tv_usec) -
                 (b->ru_stime.tv_sec * 1000000 + b->ru_stime.tv_usec)))
                / 1000000.0);
}

void generator (ll vector_size) {

	struct rusage init_time, end_time;
	double time_seq_s = 0, time_idx_s = 0, time_bin_s = 0, time_generate_vec = 0;
	ll bin_s;

	vector <ll> x;

	getrusage(RUSAGE_SELF, &init_time);
		for (ll i = 0; i < vector_size; ++i)
			x.pb (rand() % (vector_size * 5));

		sort (x.begin(), x.end());
	getrusage(RUSAGE_SELF, &end_time);

	time_generate_vec = calc_time (&init_time, &end_time);


	ll search = x[rand () % vector_size];


	getrusage(RUSAGE_SELF, &init_time);
		sequential_search (search, x);
	getrusage(RUSAGE_SELF, &end_time);

	time_seq_s = calc_time (&init_time, &end_time);


	getrusage(RUSAGE_SELF, &init_time);
		indexed_search (search, x, log10(vector_size));
	getrusage(RUSAGE_SELF, &end_time);

	time_idx_s = calc_time (&init_time, &end_time);


	getrusage(RUSAGE_SELF, &init_time);
		bin_s = binary_search (x, 0, vector_size, search);
	getrusage(RUSAGE_SELF, &end_time);

	time_bin_s = calc_time (&init_time, &end_time);


	printf ("With %lld elements, and element in position %lld:\n\n"
			"the computer took %.2lf seconds to generate and sort the array\n"
			"sequential_search took %.2lf seconds to find element\n"
			"indexed_search took %.2lf seconds to find element\n"
			"binary_search took %.2lf seconds to find element\n\n\n",
			vector_size, bin_s, time_generate_vec, time_seq_s, time_idx_s, time_bin_s);
}


int main () {
	srand (time(NULL));

	for (ll i = 100000; i < 60000000; i += 100000) {
		i += i;
		generator (i);
	}

	return 0;
}
