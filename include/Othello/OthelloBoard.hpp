#ifndef OTHELLOBOARD_HPP
#define OTHELLOBOARD_HPP
#include <tuple>
#include <memory>
#include <vector>
#include "DxLib.h"
class OthelloBoard
{
private:
    int board_size;
    std::vector<std::vector<std::vector<int>>> board; 
    bool IsInBounds(int x, int y, int z) const // ボードの範囲内かどうかをチェックする関数
    {
        return (x >= 0 && x < board_size && y >= 0 && y < board_size && z >= 0 && z < board_size);
    }
    std::tuple<int, int, int> GetDirection[26] =
        {
            {-1, -1, -1},{0, -1, -1},{1, -1, -1},
            {-1, 0, -1},{0, 0, -1},{1, 0, -1},
            {-1, 1, -1},{0, 1, -1},{1, 1, -1},

            {-1, -1, 0},{0, -1, 0},{1, -1, 0},
            {-1, 0, 0},            {1, 0, 0},
            {-1, 1, 0},{0, 1, 0},{1, 1, 0},

            {-1, -1, 1},{0, -1, 1},{1, -1, 1},
            {-1, 0, 1}, {0, 0, 1},{1, 0, 1},
            {-1, 1, 1},{0, 1, 1},{1, 1, 1},
    };

public:
    OthelloBoard()
    {
        ResetBoard(8);
    }

    void ResetBoard(int size)
    {
        board_size = size;
        board.clear();
        for(int i=0;i<board_size;++i)
        {
            std::vector<std::vector<int>> tmp2;
            for(int j=0;j<board_size;++j)
            {
                std::vector<int> tmp1;
                for(int k=0;k<board_size;++k)
                {
                    tmp1.push_back(0); 
                }
                tmp2.push_back(tmp1);
            }
            board.push_back(tmp2);
        }
        // 初期配置
        board[board_size/2-1][board_size/2-1][board_size/2-1] = 1;
        board[board_size/2-1][board_size/2-1][board_size/2] = 2;
        board[board_size/2-1][board_size/2][board_size/2-1] = 2;
        board[board_size/2-1][board_size/2][board_size/2] = 1;
        board[board_size/2][board_size/2-1][board_size/2-1] = 2;
        board[board_size/2][board_size/2-1][board_size/2] = 1;
        board[board_size/2][board_size/2][board_size/2-1] = 1;
        board[board_size/2][board_size/2][board_size/2] = 2;
        
    }
    bool PlaceStone(int color, int x, int y, int z);        // 石を置く関数
    bool IsValidMove(int color, int x, int y, int z) const; // 有効な手かどうかをチェックする関数
    bool HasValidMove(int color) const;                     // 有効な手があるかどうかをチェックする関数
    int CountReverse(int color,int x, int y, int z)const; // ひっくり返す石の数を数える関数
    int GetBoardSize() const
    {
        return board_size;
    }
    const std::vector<std::vector<std::vector<int>>>& GetBoard() const
    {
        return board;
    }
};
#endif