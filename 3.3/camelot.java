/*
ID: jonatha61
LANG: JAVA
TASK: camelot
*/

import java.io.*;
import java.util.*;

public class camelot {
	//knight's moves
	static int[] moveX = {-2, -2, -1, 1, 2, 2, 1, -1};
	static int[] moveY = {-1, 1, 2, 2, 1, -1, -2, -2};

	static int row;
	static int col;

	static int kingCol;
	static int kingRow;

	static ArrayList<Square> knights;

	static int[][][][] minMoves;

	public static void main(String[] args) throws IOException {		
		BufferedReader br = new BufferedReader(new FileReader("camelot.in"));
		PrintWriter pw = new PrintWriter(new BufferedWriter(new FileWriter("camelot.out")));

		StringTokenizer st = new StringTokenizer(br.readLine());
		row = Integer.parseInt(st.nextToken());
		col = Integer.parseInt(st.nextToken());

		//king's position
		st = new StringTokenizer(br.readLine());
		kingCol = st.nextToken().charAt(0) - 'A';
		kingRow = Integer.parseInt(st.nextToken()) - 1;

		//knight's positions
		knights = new ArrayList<Square>();
		String nextLine;
		while ((nextLine = br.readLine()) != null) {
			st = new StringTokenizer(nextLine);
			while (st.hasMoreTokens()) {
				int nextKnightCol = st.nextToken().charAt(0) - 'A';
				int nextKnightRow = Integer.parseInt(st.nextToken()) - 1;
				knights.add(new Square(nextKnightRow, nextKnightCol));
			}
		}

		//holds the min # of moves needed to go from (startRow, startCol) to (endRow, endCol)
		//minMoves[startRow][startCol][endRow][endCol];
		minMoves = new int[row][col][row][col];
		for (int[][][] r1 : minMoves) {
			for (int[][] r2 : r1) {
				for (int[] r3 : r2) {
					Arrays.fill(r3, -1);
				}
			}
		}

		//(i, j) is the start square
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				Queue<Square> q = new LinkedList<Square>();
				q.add(new Square(i, j));
				minMoves[i][j][i][j] = 0;

				while (!q.isEmpty()) {
					Square currSquare = q.remove();

					for (int k = 0; k < 8; k++) {
						int x = currSquare.row + moveX[k];
						int y = currSquare.col + moveY[k];
						if (!isValid(x, y)) continue;

						if (minMoves[i][j][x][y] == -1 || minMoves[i][j][x][y] > 1 + minMoves[i][j][currSquare.row][currSquare.col]) {
							minMoves[i][j][x][y] = 1 + minMoves[i][j][currSquare.row][currSquare.col];
							minMoves[x][y][i][j] = minMoves[i][j][x][y];
							q.add(new Square(x, y));
						}

					}
				}

			}
		}

		int answer = Integer.MAX_VALUE;
		//assume (i, j) is the final meeting point
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				answer = Math.min(answer, addKnight(i, j));
			}
		}
		pw.println(answer);
		pw.close();
	}

	//a knight picks up the king and finishes at (destX, destY)
	static int addKnight(int destX, int destY) {
		int answer = 0;

		for (Square knight : knights) {
			if (minMoves[knight.row][knight.col][destX][destY] == -1) {
				return Integer.MAX_VALUE;
			}

			answer += minMoves[knight.row][knight.col][destX][destY];
		}

		int kingToDest = Math.max(Math.abs(kingRow - destX), Math.abs(kingCol - destY));

		for (int i = Math.max(0, kingRow - 2); i <= Math.min(row - 1, kingRow + 2); i++) {
			for (int j = Math.max(0, kingCol - 2); j <= Math.min(col - 1, kingCol + 2); j++) {
				for (Square knight : knights) { 
					if (minMoves[knight.row][knight.col][i][j] != -1 && minMoves[i][j][destX][destY] != -1) {
						kingToDest = Math.min(kingToDest, Math.max(Math.abs(kingRow - i), Math.abs(kingCol - j)) + 
														  minMoves[knight.row][knight.col][i][j] + 
														  minMoves[i][j][destX][destY] - 
														  minMoves[knight.row][knight.col][destX][destY]);
					}
				}
			}
		}
		return answer + kingToDest;
	}


	static boolean isValid(int x, int y) {
		return x >= 0 && y >= 0 && x < row && y < col;
	}

	static class Square {
		int row;
		int col;

		public Square(int row, int col) {
			this.row = row;
			this.col = col;
		}
	}
}