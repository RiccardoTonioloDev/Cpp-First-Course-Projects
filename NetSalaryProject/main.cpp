#include <iostream>

using namespace std;

int main(int argc, char** argv) {
	int salary,percAllow,percDeduc;
	cout<<"Basic Salary: "<<endl;
	cin>>salary;
	cout<<"Percentage of Allowances: "<<endl;
	cin>>percAllow;
	cout<<"Percentage of Deductions: "<<endl;
	cin>>percDeduc;
	cout<<"The net worth is: "<<salary+salary*percAllow/100-salary*percDeduc/100<<endl;
	return 0;
}
