#include <bits/stdc++.h>
using namespace std;

//please change ROW and COL to desired values to check for different input sizes
#define ROW 20
#define COL 10

typedef pair<int, int> Pair;
typedef pair<double, pair<int, int> > pPair;
struct cell {
	int parent_i, parent_j;
	double f, g, h;
};

bool isValid(int row, int col) {
	return (row >= 0) && (row < ROW) && (col >= 0)
		&& (col < COL);
}

bool isUnBlocked(int grid[][COL], int row, int col) {
	if (grid[row][col] == 1) {
		return true;
	} else {
		return false;
	}
}

bool isDestination(int row, int col, Pair dest) {
	if (row == dest.first && col == dest.second) return true;
	else return false;
}

double calculateHValue(int row, int col, Pair dest) {
	return ((double)sqrt(
		(row - dest.first) * (row - dest.first)
		+ (col - dest.second) * (col - dest.second)));
}

void tracePath(cell cellDetails[][COL], Pair dest) {
	printf("\nThe Resulting Path is ");
	int row = dest.first;
	int col = dest.second;
	stack<Pair> Path;
	while (!(cellDetails[row][col].parent_i == row
			&& cellDetails[row][col].parent_j == col)) {
		Path.push(make_pair(row, col));
		int temp_row = cellDetails[row][col].parent_i;
		int temp_col = cellDetails[row][col].parent_j;
		row = temp_row;
		col = temp_col;
	}
	Path.push(make_pair(row, col));
	while (!Path.empty()) {
		pair<int, int> p = Path.top();
		Path.pop();
		printf("-> (%d,%d) ", p.first, p.second);
	}
	return;
}

void aStarSearch(int grid[][COL], Pair src, Pair dest) {
	if (isValid(src.first, src.second) == false) {
		printf("Source is invalid\n");
		return;
	}
	if (isValid(dest.first, dest.second) == false) {
		printf("Destination is invalid\n");
		return;
	}
	if (isUnBlocked(grid, src.first, src.second) == false
		|| isUnBlocked(grid, dest.first, dest.second)
			== false) {
		printf("Source or the destination is blocked\n");
		return;
	}
	if (isDestination(src.first, src.second, dest)
		== true) {
		printf("We are already at the destination\n");
		return;
	}
	bool closedList[ROW][COL];
	memset(closedList, false, sizeof(closedList));
	cell cellDetails[ROW][COL];
	int i, j;
	for (i = 0; i < ROW; i++) {
		for (j = 0; j < COL; j++) {
			cellDetails[i][j].f = FLT_MAX;
			cellDetails[i][j].g = FLT_MAX;
			cellDetails[i][j].h = FLT_MAX;
			cellDetails[i][j].parent_i = -1;
			cellDetails[i][j].parent_j = -1;
		}
	}
	i = src.first, j = src.second;
	cellDetails[i][j].f = 0.0;
	cellDetails[i][j].g = 0.0;
	cellDetails[i][j].h = 0.0;
	cellDetails[i][j].parent_i = i;
	cellDetails[i][j].parent_j = j;
	set<pPair> openList;
	openList.insert(make_pair(0.0, make_pair(i, j)));
	bool foundDest = false;
	while (!openList.empty()) {
		pPair p = *openList.begin();
		openList.erase(openList.begin());
		i = p.second.first;
		j = p.second.second;
		closedList[i][j] = true;
		double gNew, hNew, fNew;
		for (int temp1=-1;temp1<=1;temp1++) {
			for (int temp2=-1;temp2<=1;temp2++) {
				if (temp1==0 && temp2==0) continue;
				if (isValid(i+temp1, j+temp2) == true) {
					if (isDestination(i+temp1, j+temp2, dest) == true) {
						cellDetails[i+temp1][j+temp2].parent_i = i;
						cellDetails[i+temp1][j+temp2].parent_j = j;
						printf("The destination cell is found\n");
						tracePath(cellDetails, dest);
						foundDest = true;
						return;
					} else if (closedList[i+temp1][j+temp2] == false
							&& isUnBlocked(grid, i+temp1, j+temp2)
									== true) {
						gNew = cellDetails[i][j].g + 1.0;
						hNew = calculateHValue(i+temp1, j+temp2, dest);
						fNew = gNew + hNew;
						if (cellDetails[i+temp1][j+temp2].f == FLT_MAX
							|| cellDetails[i+temp1][j+temp2].f > fNew) {
							openList.insert(make_pair(
								fNew, make_pair(i+temp1, j+temp2)));
							cellDetails[i+temp1][j+temp2].f = fNew;
							cellDetails[i+temp1][j+temp2].g = gNew;
							cellDetails[i+temp1][j+temp2].h = hNew;
							cellDetails[i+temp1][j+temp2].parent_i = i;
							cellDetails[i+temp1][j+temp2].parent_j = j;
						}
					}
				}
			}
		}
	}
	if (foundDest == false)
		printf("Failed to find the Destination Cell\n");

	return;
}

int32_t main() {
	int grid[ROW][COL];
    for (int i=0;i<ROW;i++) {
        for (int j=0;j<COL;j++) {
            grid[i][j]=0+rand()%2;
        }
    }
	grid[ROW-1][0]=1;
	grid[0][0]=1;
	Pair src = make_pair(ROW-1, 0);
	Pair dest = make_pair(0, 0);
    clock_t start=clock();
	aStarSearch(grid, src, dest);
    clock_t stop=clock();
    cout<<"\n\ntime: "<<(stop-start)/(double)CLOCKS_PER_SEC<<" sec\n\n";
	return (0);
}
