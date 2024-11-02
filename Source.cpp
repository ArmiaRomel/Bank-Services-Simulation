// Author: Armia Romel
#include<iostream>

using namespace std;

//this function is for generating random number depends on the range we give it
int randint(int start, int end) {

	static int seed = 0;
	if (seed == 0) {
		srand(time(0));
		seed = 1;
	}
	return rand() % (end - start + 1) + start;
}


int main() {

	cout << "Customer || IAT || ST || Arrival Time || Service Start || Servicce End || Waiting Time || Queue Lenght || Idle";
	cout << endl;
	//cout << "   8     || 8   || 1  ||      8       ||      8        ||      8       ||      8       ||       8      ||   8 ";

	int iat, st, arrival = 0, service_end = 0, service_start, waiting_time, arr[101], j, queue, sum_of_waiting_time = 0, max_queue = 0, sum_of_idle = 0, queue_idle, customers_who_wait = 0;

	// in this array we record the service end of each customer
	arr[0] = 0;

	// in this for loop we calculate all the attributes of one customer at a time
	for (int i = 0; i < 100; i++) {

		// calculating random number from randint function for IAT
		iat = randint(1, 7);
		// calculating random number from randint function for ST
		st = randint(4, 8);

		// we calculate arrival time according to IAT and previous IAT
		arrival += iat;

		// we determine service start time by comparing previous service end time and customer arrival time
		if (arrival >= service_end) {
			service_start = arrival;
		}
		else {
			service_start = service_end;
		}

		// we calculate service end time
		service_end = service_start + st;

		// calculating customer waiting time
		waiting_time = service_start - arrival;

		// recording customer service end that helps us determine the queue of the next customers
		arr[i + 1] = service_end;

		j = i;

		// resitting queue value to 0 so we can calculate this customer queue
		queue = 0;
		queue_idle = 0;

		// in this for loop we compering this customer arrival time to his previous cutomers service end so we determine this customer queue value
		for (j; j >= 0; j--) {
			if (arrival >= arr[j]) {
				break;
			}
			else {
				queue += 1;
			}
		}

		if (queue > 0) {
			customers_who_wait += 1;
		}

		// this if condition calculate idle value of the service and then it calculate the sum of idle
		if (arrival > arr[i]) {
			queue_idle = arrival - arr[i];
			sum_of_idle = sum_of_idle + (arrival - arr[i]);
		}

		cout << "   C" << i + 1 << "        " << iat << "      " << st << "          " << arrival << "               " << service_start << "                " << service_end << "              " << waiting_time << "              " << queue << "           " << queue_idle;
		cout << endl;

		// calculating the sum of waiting time
		sum_of_waiting_time += waiting_time;

		// this if condition determine the maximum queue
		if (queue > max_queue) {
			max_queue = queue;
		}
	}

	cout << endl << endl;

	// calculating average waiting time
	float average_waiting_time = (float)sum_of_waiting_time / 100;

	cout << "Average Waiting Time = " << average_waiting_time << endl;

	cout << "Maximum Queue Length = " << max_queue << endl;

	// calculating percentage of idleness // arr[10] is the last service end of the last customer
	double percentage_of_idleness = ((float)sum_of_idle / (float)arr[100]) * 100;

	cout << "Percentage of Idleness of The Server = " << percentage_of_idleness << "%" << endl;

	//calculating Probability That a Customer Has To Wait
	float probability_that_a_customer_has_to_wait = (float)customers_who_wait / 100;

	cout << "Probability That a Customer Has To Wait = " << probability_that_a_customer_has_to_wait << endl;

	//calculating Average Waiting Time To Those Who Wait
	float average_waiting_time_to_those_who_wait = (float)sum_of_waiting_time / (float)customers_who_wait;

	cout << "Average Waiting Time To Those Who Wait = " << average_waiting_time_to_those_who_wait << " Sec" << endl << endl;

	return 0;
}