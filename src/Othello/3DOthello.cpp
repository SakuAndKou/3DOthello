#include "Othello/3DOthello.hpp"

void _3DOthello::Initialize(int num)
{
    XVector = VGet(1.0f, 0.0f, 0.0f);
    YVector = VGet(0.0f, 1.0f, 0.0f);
    ZVector = VGet(0.0f, 0.0f, 1.0f);
    XRotate = 0.0f;
    YRotate = 0.0f;
    ZRotate = 0.0f;
    cameraPosition = VGet(0.0f, 60.0f, -60.0f); // カメラの初期位置
    board.ResetBoard(num);                      // ボードの初期化
    std::mt19937 mt{ std::random_device{}() };
    std::uniform_int_distribution<int> dist(1, 2);
    mycolor = dist(mt); // ランダムに自分の色を決定
}
void _3DOthello::Finalize()
{
}

void _3DOthello::Update()
{
    ControlCamera();
    if (CheckHitKey(KEY_INPUT_ESCAPE) == 1)
    {
        // ESCキーでシーンを終了
        ChangeScene(1); // 例として、シーン1に戻る
    }
}
void _3DOthello::Draw()
{
    SetCameraNearFar(1.0f, 150.0f);
    SetUseLighting(FALSE);
    SetWriteZBuffer3D(TRUE);
    SetUseZBuffer3D(TRUE);
    // DrawStringToHandle( 100, 100, _T("Start Scene"), GetColor(255, 255, 255),FontHandle);

    SetDrawBlendMode(DX_BLENDMODE_ALPHA, 64);

    auto boardState = board.GetBoard();   // ボードの状態を取得
    int boardSize = board.GetBoardSize(); // ボードのサイズを取得
    for (int i = -10 * boardSize / 2; i <= 10 * boardSize / 2; i += 10)
    {
        for (int j = -10 * boardSize / 2; j <= 10 * boardSize / 2; j += 10)
        {
            DrawLine3D(VGet(i, j, -10 * boardSize / 2), VGet(i, j, 10 * boardSize / 2), GetColor(0, 0, 0));
            DrawLine3D(VGet(i, -10 * boardSize / 2, j), VGet(i, 10 * boardSize / 2, j), GetColor(0, 0, 0));
            DrawLine3D(VGet(-10 * boardSize / 2, i, j), VGet(10 * boardSize / 2, i, j), GetColor(0, 0, 0));
        }
    }
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, 256);

    for (int x = 0; x < boardSize; ++x)
    {
        for (int y = 0; y < boardSize; ++y)
        {
            for (int z = 0; z < boardSize; ++z)
            {
                if (boardState[x][y][z] == 1) // 黒石
                {
                    DrawSphere3D(VGet(x * 10 - 10 * boardSize / 2 + 5, y * 10 - 10 * boardSize / 2 + 5, z * 10 - 10 * boardSize / 2 + 5), 4, 32, GetColor(0, 0, 0), GetColor(0, 0, 0), TRUE);
                }
                else if (boardState[x][y][z] == 2) // 白石
                {
                    DrawSphere3D(VGet(x * 10 - 10 * boardSize / 2 + 5, y * 10 - 10 * boardSize / 2 + 5, z * 10 - 10 * boardSize / 2 + 5), 4, 32, GetColor(255, 255, 255), GetColor(255, 255, 255), TRUE);
                }
            }
        }
    }

    int mouseX1, mouseY1;
    // マウスの位置を取得
    GetMousePoint(&mouseX1, &mouseY1);
    Rot += GetMouseWheelRotVol() / 1000.0f;
    Rot = std::clamp(Rot, 0.95f, 1.0f);
    auto WorldPos = ConvScreenPosToWorldPos(VGet(mouseX1, mouseY1, Rot));
    DrawSphere3D(WorldPos, 1, 32, GetColor(255, 0, 0), GetColor(255, 0, 0), TRUE);
    if (WorldPos.x >= -10 * boardSize / 2 && WorldPos.x <= 10 * boardSize / 2 &&
        WorldPos.y >= -10 * boardSize / 2 && WorldPos.y <= 10 * boardSize / 2 &&
        WorldPos.z >= -10 * boardSize / 2 && WorldPos.z <= 10 * boardSize / 2)
    {
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
        DrawCube3D(VGet(floorf(WorldPos.x / 10) * 10, floorf(WorldPos.y / 10) * 10, floorf(WorldPos.z / 10) * 10), VGet((floorf(WorldPos.x / 10) * 10 + 10.0f), (floorf(WorldPos.y / 10) * 10 + 10.0f), (floorf(WorldPos.z / 10) * 10 + 10.0f)), GetColor(255, 0, 0), GetColor(255, 0, 0), TRUE);
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, 256);
    }

    

    if(mycolor == 1)
        DrawStringToHandle(0, 0, _T("player is black"), GetColor(0, 0, 0), FontHandle);
    else
        DrawStringToHandle(0, 0, _T("player is white"), GetColor(0, 0, 0), FontHandle);

    if(color == 1)
        DrawStringToHandle(0, 30, _T("black's turn"), GetColor(0, 0, 0), FontHandle);
    else
        DrawStringToHandle(0, 30, _T("white's turn"), GetColor(0, 0, 0), FontHandle);
    

    // DrawSphere3D(VGet(0, 0, 0), 5,32, GetColor(255, 255, 255), GetColor(255, 255, 255),TRUE);
    // DrawLine3D(VGet(0, 0, 0), 80 * XVector, GetColor(255, 0, 0));
    // DrawLine3D(VGet(0, 0, 0), 80 * YVector, GetColor(0, 255, 0));
    // DrawLine3D(VGet(0, 0, 0), 80 * ZVector, GetColor(0, 0, 255));
    // DrawFormatString(0, 0, GetColor(0, 0, 0), _T("XRotate: %.2f, YRotate: %.2f, ZRotate: %.2f"), XRotate, YRotate, ZRotate);
    // DrawFormatString(0, 20, GetColor(0, 0, 0), _T("XVectorx: %.2f,XVectory: %.2f,XVectorz: %.2f"), XVector.x, XVector.y, XVector.z);
    // DrawFormatString(0, 40, GetColor(0, 0, 0), _T("YVectorx: %.2f,YVectory: %.2f,YVectorz: %.2f"), YVector.x, YVector.y, YVector.z);
    // DrawFormatString(0, 60, GetColor(0, 0, 0), _T("ZVectorx: %.2f,ZVectory: %.2f,ZVectorz: %.2f"), ZVector.x, ZVector.y, ZVector.z);
    // DrawFormatString(0, 80, GetColor(0, 0, 0), _T("cameraPositionx: %.2f,cameraPositiony: %.2f,cameraPositionz: %.2f"), cameraPosition.x, cameraPosition.y, cameraPosition.z);
    // DrawFormatString(0, 100, GetColor(0, 0, 0), _T("Rot: %.2f"), Rot);
    // DrawFormatString(0, 120, GetColor(0, 0, 0), _T("bool: %d"), result);
    // DrawFormatString(0, 140, GetColor(0, 0, 0), _T("x: %d,y: %f,z: %f"), (int)floorf(WorldPos.x / 10.0f), (WorldPos.y / 10.0f), (WorldPos.z / 10.0f));
    // DrawFormatString(0, 180, GetColor(255, 0, 0), _T("A:%d"), boardState[boardSize / 2 - 1][boardSize / 2 - 1][boardSize / 2 - 1]);
    if(!FinishGame(boardSize, boardState)) // ゲーム終了の処理
        GameLogic(WorldPos, boardSize); // ゲームのロジックを実行
}
void _3DOthello::GameLogic(VECTOR WorldPos,int boardSize){
    if(color==mycolor)
    {
        int ClickX, ClickY, Button, LogType;
        if (GetMouseInputLog2(&Button, &ClickX, &ClickY, &LogType, TRUE) == 0)
        {
            if (Button == MOUSE_INPUT_LEFT && LogType == MOUSE_INPUT_LOG_DOWN)
            {

                int x = floorf(WorldPos.x / 10.0f) + boardSize / 2; // オセロボードの座標に変換
                int y = floorf(WorldPos.y / 10.0f) + boardSize / 2;
                int z = floorf(WorldPos.z / 10.0f) + boardSize / 2;
                if (board.IsValidMove(color, x, y, z))
                {
                    result = board.PlaceStone(color, x, y, z); // オセロボードに石を置く
                    color = (color == 1) ? 2 : 1;              // 石の色を切り替える
                    auto now = std::chrono::system_clock::now();
                    last_Time = now;
                }
            }
        }
    }
    else
    {
        auto now = std::chrono::system_clock::now();
        if(std::chrono::duration_cast<std::chrono::milliseconds>(now - last_Time).count() < 2000) // 2秒ごとにAIの手を打つ
        {
            return;
        }
        int max_count = 0;
        int tmpx = 0, tmpy = 0, tmpz = 0;
        for (int x = 0; x < boardSize; x++)
        {
            for (int y = 0; y < boardSize; y++)
            {
                for (int z = 0; z < boardSize; z++)
                {
                    int tmp = board.CountReverse(color, x, y, z);
                    if (tmp > max_count)
                    {
                        max_count = tmp;
                        tmpx = x;
                        tmpy = y;
                        tmpz = z;
                    }
                }
            }
        }
        board.PlaceStone(color, tmpx, tmpy, tmpz);
        color = (color == 1) ? 2 : 1;              // 石の色を切り替える
    }
}
void _3DOthello::ControlCamera(){
    // キーボード入力の処理
    // if (CheckHitKey(KEY_INPUT_LSHIFT) == 1)
    // {
    //     // 左右キーでカメラの捻り方向回転値を変更
    //     if (CheckHitKey(KEY_INPUT_LEFT) == 1)
    //     {
    //         ZRotate += DX_PI_F / 60.0f;
    //     }
    //     if (CheckHitKey(KEY_INPUT_RIGHT) == 1)
    //     {
    //         ZRotate -= DX_PI_F / 60.0f;
    //     }
    // }
    // else
    // {
    //     // 左右キーでカメラの水平方向回転値を変更
    //     if (CheckHitKey(KEY_INPUT_LEFT) == 1)
    //     {
    //         YRotate -= DX_PI_F / 60.0f;
    //         ZVector = Rotate(ZVector, YVector, -DX_PI_F / 60.0f);
    //         XVector = Rotate(XVector, YVector, -DX_PI_F / 60.0f);
    //     }
    //     if (CheckHitKey(KEY_INPUT_RIGHT) == 1)
    //     {
    //         YRotate += DX_PI_F / 60.0f;
    //         ZVector = Rotate(ZVector, YVector, DX_PI_F / 60.0f);
    //         XVector = Rotate(XVector, YVector, DX_PI_F / 60.0f);
    //     }
    // }

            // 左右キーでカメラの水平方向回転値を変更
        if (CheckHitKey(KEY_INPUT_LEFT) == 1)
        {
            YRotate -= DX_PI_F / 60.0f;
            ZVector = Rotate(ZVector, YVector, -DX_PI_F / 60.0f);
            XVector = Rotate(XVector, YVector, -DX_PI_F / 60.0f);
        }
        if (CheckHitKey(KEY_INPUT_RIGHT) == 1)
        {
            YRotate += DX_PI_F / 60.0f;
            ZVector = Rotate(ZVector, YVector, DX_PI_F / 60.0f);
            XVector = Rotate(XVector, YVector, DX_PI_F / 60.0f);
        }

    // 上下キーでカメラの垂直方向回転値を変更
    if (CheckHitKey(KEY_INPUT_UP) == 1)
    {
        XRotate -= DX_PI_F / 60.0f;
    }
    if (CheckHitKey(KEY_INPUT_DOWN) == 1)
    {
        XRotate += DX_PI_F / 60.0f;
    }
    if ((GetMouseInput() & MOUSE_INPUT_MIDDLE) != 0)
    {
        if (!isMousePressed)
        {
            isMousePressed = true;
            GetMousePoint(&mouseX, &mouseY);
        }
        else
        {
            int newMouseX, newMouseY;
            GetMousePoint(&newMouseX, &newMouseY);
            int deltaX = newMouseX - mouseX;
            int deltaY = newMouseY - mouseY;

            // マウスの動きに応じて回転値を変更
            YRotate -= deltaX * 0.005f; // 水平方向
            XRotate -= deltaY * 0.005f; // 垂直方向

            ZVector = Rotate(ZVector, YVector, -deltaX * 0.005f);
            XVector = Rotate(XVector, YVector, -deltaX * 0.005f);

            // マウスの位置を更新
            mouseX = newMouseX;
            mouseY = newMouseY;
        }
    }
    else
    {
        isMousePressed = false; // マウスが離されたらフラグをリセット
    }

    if (CheckHitKey(KEY_INPUT_LSHIFT) == 1)
    {
        if (CheckHitKey(KEY_INPUT_W) == 1)
        {
            cameraPosition = cameraPosition + YVector;
        }
        if (CheckHitKey(KEY_INPUT_S) == 1)
        {
            cameraPosition = cameraPosition - YVector;
        }
    }
    else
    {
        if (CheckHitKey(KEY_INPUT_W) == 1)
        {
            cameraPosition = cameraPosition + ZVector;
        }
        if (CheckHitKey(KEY_INPUT_S) == 1)
        {
            cameraPosition = cameraPosition - ZVector;
        }
    }

    if (CheckHitKey(KEY_INPUT_D) == 1)
    {
        cameraPosition = cameraPosition + XVector;
    }
    if (CheckHitKey(KEY_INPUT_A) == 1)
    {
        cameraPosition = cameraPosition - XVector;
    }
    // カメラの位置と角度を設定
    SetCameraPositionAndAngle(cameraPosition, XRotate, YRotate, ZRotate);

}
bool _3DOthello::FinishGame(int boardSize, const std::vector<std::vector<std::vector<int>>>& boardState){
    if (!board.HasValidMove(color))
    {
        color = (color == 1) ? 2 : 1; // 石の色を切り替える
        if (!board.HasValidMove(color))
        {
            DrawStringToHandle(0, 200, _T("Game Over!"),GetColor(255, 255, 255), FontHandle);
            DrawStringToHandle(0, 220,  _T("Press ESC to exit."),GetColor(255, 255, 255), FontHandle);
            int blackCount = 0, whiteCount = 0;
            for(std::vector<std::vector<std::vector<int>>>::const_iterator x = boardState.begin(); x != boardState.end(); x++)
            {
                for(std::vector<std::vector<int>>::const_iterator y = x->begin(); y != x->end(); y++)
                {
                    for(std::vector<int>::const_iterator z = y->begin(); z != y->end(); z++)
                    {
                        if (*z == 1)
                        {
                            blackCount++;
                        }
                        else if (*z == 2)
                        {
                            whiteCount++;
                        }
                    }
                }
            }
            if (blackCount > whiteCount)
            {
                DrawStringToHandle(0, 240, _T("Black wins!"), GetColor(255, 255, 255), FontHandle);
            }
            else if (whiteCount > blackCount)
            {
                DrawStringToHandle(0, 240, _T("White wins!"), GetColor(255, 255, 255), FontHandle);
            }
            else
            {
                DrawStringToHandle(0, 240, _T("It's a draw!"), GetColor(255, 255, 255), FontHandle);

            }
            return true;
        }
    }
    return false;
}
void _3DOthello::ChangeScene(int num)
{
    // シーン変更の処?��?
    manager.lock()->ChangeScene(num); // 例として、次のシーンに変更
}