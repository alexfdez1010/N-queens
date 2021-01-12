#include <iostream>
#include <fstream>
#include <ctime>

#define clz(x) __builtin_clz(x)

using namespace std;

typedef long long ull;

unsigned int n;
ull allTrue,res;
int *sol;
bool found,onlySolution,chessboard;

ull log2(ull n){
	return 31-clz(n);
}


void outputSolutionBoard(ostream &stream){

	unsigned short int i,j;

	for(j = 0;j < n;j++){
		stream << "----";
	}
	stream << "-\n";

	for(i = 0;i < n;i++){
		for(j = 0;j < n;j++){
			if(j == sol[i]){
				stream << "| Q ";
			}
			else{
				stream << "|   ";
			}
		}
		stream << "|\n";
		for(j = 0;j < n;j++){
			stream << "----";
		}
		stream << "-\n";
	}
	stream << endl;

}

void outputSolutionArray(ostream &stream){
	unsigned short int i;

	for(i = 0;i < n;i++){
		stream << sol[i] << " ";
	}
	stream << endl;
}

void solveR(ull rows,ull leftDia,ull rightDia,unsigned int col,ostream &stream){
	if(rows == allTrue){
		found = true;
		res++;
		if(chessboard){
			outputSolutionBoard(stream);
		}
		else{
			outputSolutionArray(stream);
		}
		return;
	}
	if(!(onlySolution && found)){
		ull allow,pos,row;
		allow = allTrue & ~(rows | leftDia | rightDia);
		while(allow){
			pos = allow & -allow;
			allow -= pos;
			row = log2(pos);
			sol[col] = row;
			solveR(rows | pos, (leftDia | pos) << 1, (rightDia | pos) >> 1,col+1,stream);
			sol[col] = -1;
		}
	}
}

void solve(ostream &stream){
	allTrue = (1 << n) - 1;
	sol = new int[n];
	found = false;
	solveR(0,0,0,0,stream);
}

int main(){
	char sel;
	string filename;
	fstream file;
	time_t start,end;

	res = 0;

	cout << "Input the number of queens to put in the chessboard: ";
	cin >> n;

	cout << "Do you want all solutions?(Y/N): ";
	cin >> sel;
	onlySolution = sel == 'N';

	cout << "Print the solutions in a chessboard?(Y/N): ";
	cin >> sel;
	chessboard = sel == 'Y';

	filename = (chessboard)? "board" : "array";
	filename = to_string(n) + "-queens-" + filename +".txt";

	file.open(filename, ios :: out | ios :: trunc);
	time(&start);
	solve(file);
	time(&end);
	file.close();

	cout << "The program has needed " << double(end-start) << " seconds to finish\n";

	if(!onlySolution){
		cout << "There are in total " << res << " solutions";
	}

	return 0;
}






