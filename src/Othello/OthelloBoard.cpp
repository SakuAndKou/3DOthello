#include "Othello/OthelloBoard.hpp"
bool OthelloBoard::PlaceStone(int color, int x, int y, int z)
{
    if (!IsInBounds(x, y, z)) return false; // 範囲外なら置けない
    if (board[x][y][z] != 0) return false; // そのセルが空でなければ置けない
    if (!IsValidMove(color, x, y, z)) return false; // 有効な手でなければ置けない

    board[x][y][z] = color; // 石を置く
    // 石を置いた後、周囲の相手の石をひっくり返す
    for (auto [dx, dy, dz] : GetDirection)
    {
        int nx = x + dx, ny = y + dy, nz = z + dz;
        if (!IsInBounds(nx, ny, nz) || board[nx][ny][nz] == 0 || board[nx][ny][nz] == color) continue;

        while (IsInBounds(nx, ny, nz) && board[nx][ny][nz] != 0)
        {
            if (board[nx][ny][nz] == color)
            {
                // 自分の石に到達した場合、間の相手の石をひっくり返す
                for (int px = x + dx, py = y + dy, pz = z + dz; px != nx || py != ny || pz != nz; px += dx, py += dy, pz += dz)
                {
                    board[px][py][pz] = color;
                }
                break;
            }
            nx += dx; ny += dy; nz += dz;
        }
    }
    return true; // 石を置くことができた
}
bool OthelloBoard::IsValidMove(int color, int x, int y, int z) const
{
    if(!IsInBounds(x,y,z))return false; // 範囲外なら無効な手
    if(board[x][y][z] != 0)return false; // そのセルが空でなければ無効な手
    bool result = false; // 有効な手かどうかのフラグ
    for(auto [dx,dy,dz] : GetDirection)
    {
        int nx = x + dx, ny = y + dy, nz = z + dz; // 隣接するセルの座標
        if(!IsInBounds(nx, ny, nz))continue; // 範囲外なら次の方向へ
        if (board[nx][ny][nz] == 0) continue; // 空のセルなら次の方向へ
        if (board[nx][ny][nz] == color) continue; // 自分と同じ色の石であったら次の方向へ

        // 隣接するセルが相手の石であった場合、さらにその方向に進む
        while (IsInBounds(nx, ny, nz) && board[nx][ny][nz] != 0)
        {
            if (board[nx][ny][nz] == color) // 自分の石に到達した場合
            {
                result = true; // 有効な手とする
                goto label1; // 有効な手が見つかったのでループを抜ける
            }
            nx += dx; ny += dy; nz += dz;
        }
    }
    label1:
        return result; // 有効な手かどうかを返す

}
bool OthelloBoard::HasValidMove(int color) const
{
    for (int x = 0; x < board_size; ++x)
    {
        for (int y = 0; y < board_size; ++y)
        {
            for (int z = 0; z < board_size; ++z)
            {
                if (IsValidMove(color, x, y, z))
                {
                    return true;
                }
            }
        }
    }
    return false;
}
int OthelloBoard::CountReverse(int color,int x, int y, int z) const
{
    if(!IsInBounds(x,y,z))return false; // 範囲外なら無効な手
    if(board[x][y][z] != 0)return false; // そのセルが空でなければ無効な手
    int flipCount = 0; // ひっくり返す石の数
    for(auto [dx,dy,dz] : GetDirection)
    {
        int nx = x + dx, ny = y + dy, nz = z + dz; // 隣接するセルの座標
        if(!IsInBounds(nx, ny, nz))continue; // 範囲外なら次の方向へ
        if (board[nx][ny][nz] == 0) continue; // 空のセルなら次の方向へ
        if (board[nx][ny][nz] == color) continue; // 自分と同じ色の石であったら次の方向へ

        // 隣接するセルが相手の石であった場合、さらにその方向に進む
        int count = 0; // ひっくり返す石の数
        while (IsInBounds(nx, ny, nz) && board[nx][ny][nz] != 0)
        {
            if (board[nx][ny][nz] == color) // 自分の石に到達した場合
            {
                flipCount += count; // ひっくり返す石の数を加算
            }
            nx += dx; ny += dy; nz += dz;
            count++;
        }
    }
    return flipCount; // 有効な手かどうかを返す
}