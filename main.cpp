//
// Created by Kelly Lam on 4/4/2021.
//

#include <iostream>
#include "linearlist.h"
#include "queue.h"

using namespace std;

int
    dC[] = {0, 1, 1, 0, -1, -1},
    dREven[] = {-1, -1, 0, 1, 0, -1},
    dROdd[] = {-1, 0, 1, 1, 1, 0},
    *dR,
    map[20][20];

int encode(int row, int col) {
    return col + row * 20;
}

void decode(int &row, int &col, int enc) {
    col = enc % 20;
    row = enc / 20;
}

void generateMap(int map[][20], int ipRow, int ipCol) {
    // first number every cell as -1
    for (int i=0; i<20; i++) {
        for (int j=0; j<20; j++)
            if (map[i][j] != -2) {
                map[i][j] = -1;
            }
    }

    Queue<int> pathFinder;
    pathFinder.clear();

    map[ipRow][ipCol] = 0;
    pathFinder.enqueue(encode(ipRow, ipCol));

    int loc = 0, nR, nC, r, c;

    // then number the map w/ phosdex starting as 0
    while (!pathFinder.isEmpty()) {
        loc = pathFinder.dequeue();
        decode(r, c, loc);
        dR = dREven;

        if (c & 1)
            dR = dROdd;

        for (int d=0;d<6;d++) {
            nR = r + dR[d];
            nC = c + dC[d];

            if ((0 <= nC) && (nC < 20) && (0 <= nR) && (nR < 20)) {
                if (map[nR][nC] == -1) {
                    pathFinder.enqueue(encode(nR, nC));
                    map[nR][nC] = map[r][c]+1;
                }
            }
        }
    }
}

void findPath(int map[][20], int row, int col, LinearList<int> &path) {
    path.clear();
    int nR, nC;
    int listCount = 0;

    if (map[row][col] == -1) {
        return; // there is no path
    } else {
        path.insert(listCount, encode(row, col));
        listCount += 1;
        while (map[row][col] != 0) {
            dR = dREven;

            if (col & 1)
                dR = dROdd;

            for (int d = 0; d < 6; d++) {
                nR = row + dR[d];
                nC = col + dC[d];

                if (map[nR][nC] == map[row][col]-1) {
                    path.insert(listCount, encode(nR, nC));
                    listCount += 1;
                    row = nR;
                    col = nC;
                }
            }
        }
    }
}

int main() {
    int ddRow, ddCol,
        mmRow, mmCol,
        ipRow, ipCol,
        lavaSpaces,
        lavaRow, lavaCol;
    LinearList<int> duckPath, mmPath1, mmPath2;

    cout << "Enter the row and column for Duck Dodgers, Marvin the Martian, the Illudium Phosdex, "
            "and the amount of lava spaces: " << endl;
    cin >> ddRow >> ddCol >> mmRow >> mmCol >> ipRow >> ipCol >> lavaSpaces;

    for (int i=0; i<lavaSpaces; i++) {
        cout << "Enter the row and column for a lava space: " << endl;
        cin >> lavaRow >> lavaCol;
        map[lavaRow][lavaCol] = -2; // lava spaces are marked before generating map to save time
    }

    generateMap(map, ipRow, ipCol);
    findPath(map, ddRow, ddCol, duckPath);
    findPath(map, mmRow, mmCol, mmPath1);

    if (duckPath.isEmpty()) {
        if (mmPath1.isEmpty()) {
            cout << "Nobody wins because there is no path to the Illudium Phosdex." << endl;
            return 0;
        } else {
            cout << "Duck Dodgers loses because he does not have a path to the Illudium Phosdex." << endl;
            return 0;
        }
    } else {
        if (mmPath1.isEmpty()) {
            cout << "Duck Dodgers reaches the Illudium Phosdex first because Marvin can't reach it." << endl;
            return 0;
        } else if (duckPath.size() < mmPath1.size()) {
            cout << "Duck Dodgers reaches the Illudium Phosdex first." << endl;
            return 0;
        } else {
            // for loop for each pos in mmPath1 except start & end
            for (int i = 1; i < mmPath1.size()-1; i++) {
                int posR, posC;
                decode(posR, posC, mmPath1[i]);
                map[posR][posC] = -2; // this is gandalf
                generateMap(map, ipRow, ipCol);
                findPath(map, ddRow, ddCol, duckPath);
                findPath(map, mmRow, mmCol, mmPath2);
                if (!duckPath.isEmpty() && duckPath.size() < mmPath2.size()) {
                    cout << "Duck and Marvin will reach the Illudium Phosdex simultaneously, trying Gandalf." << endl;
                    cout << "The Space Cadet summons Gandalf to (" << posR << ", " << posC << ")." << endl;
                    return 0;
                }
                map[posR][posC] = -1;
            }
        }
    }
    cout << "Marvin the Martian will reach the Illudium Phosdex first, trying Gandalf." << endl;
    cout << "Gandalf cannot help." << endl;
    return 0;
}
