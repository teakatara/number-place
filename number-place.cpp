#include <iostream>

using std::cin;
using std::cout;
using std::endl;

#define FIELD_LENGTH 9
#define AREA_LENGTH 3

#define DEBUG_FLAG false
#define DEBUG_DETAIL_FLAG false

void solvNumberPlaceFunc(int field[FIELD_LENGTH][FIELD_LENGTH], int xOffset, int yOffset, bool *finishFlag);
bool checkValidationFunc(int field[FIELD_LENGTH][FIELD_LENGTH], int xOffset, int yOffset);
void printField(int field[FIELD_LENGTH][FIELD_LENGTH]);

int main() {
  // フィールドの宣言
  int field[FIELD_LENGTH][FIELD_LENGTH];

  // 終了判定用のフラグ
  bool finishFlag = false;
  bool *finishFlagPointer = &finishFlag;

  // フィールドの初期化
  for (int i = 0; i < FIELD_LENGTH; i++) {
    for (int j = 0; j < FIELD_LENGTH; j++) {
      cin >> field[i][j];
    }
  }
  
  if (DEBUG_FLAG) {
    printField(field);
    cout << endl;
  }

  try {
    solvNumberPlaceFunc(field, 0, 0, finishFlagPointer);
  } catch(char *str) {
    cout << str;
  }

  return 0;
}

void solvNumberPlaceFunc(int field[FIELD_LENGTH][FIELD_LENGTH], int xOffset, int yOffset, bool *finishFlag) {
  if (DEBUG_FLAG) {
    cout << xOffset << ":" << yOffset << endl;
    printField(field);
    cout << endl;
  }
  
  // 右下のセルまで探索が終わった場合
  if (yOffset == FIELD_LENGTH) {
    // 現在の盤面を表示してreturn
    printField(field);
    *finishFlag = true;
    return;
  }

  // 初期値の場合
  if (field[yOffset][xOffset] != 0) {
    // 次のセルに移動
    int nextXOffset = (xOffset + 1) % FIELD_LENGTH;
    int nextYOffset = yOffset;
    if (nextXOffset == 0) {
      nextYOffset += 1;
    }
    solvNumberPlaceFunc(field, nextXOffset, nextYOffset, finishFlag);
    return;
  }

  // 空欄のセルの場合
  for (int num = 1; num <= 9; num++) {
    // 値を仮代入
    field[yOffset][xOffset] = num;
    
    // 仮代入値で問題ないかチェック
    // チェックが通った場合
    if (checkValidationFunc(field, xOffset, yOffset)) {
      // 次のセルに移動
      int nextXOffset = (xOffset + 1) % FIELD_LENGTH;
      int nextYOffset = yOffset;
      if (nextXOffset == 0) {
        nextYOffset += 1;
      }
      solvNumberPlaceFunc(field, nextXOffset, nextYOffset, finishFlag);
      
      
      // finishFlagがtrueの場合
      if (*finishFlag) {
        // 解が見つかったということなのでreturn;
        return;
      }
    }
    field[yOffset][xOffset] = 0;
  }

  return;
}

bool checkValidationFunc(int field[FIELD_LENGTH][FIELD_LENGTH], int xOffset, int yOffset) {
  // チェック対象値
  int targetValue = field[yOffset][xOffset];

  // y軸チェック
  for (int i = 0; i < FIELD_LENGTH; i++) {
    // 対象値と同じ座標はスキップ
    if (yOffset == i) {
      continue;
    }

    // 対象値と同じ値があった場合はfalseをreturn
    if (field[i][xOffset] == targetValue) {
      if (DEBUG_FLAG && DEBUG_DETAIL_FLAG) {
        cout << "checkValidationFunc:vertical" << endl;
        cout << xOffset << ":" << yOffset << endl;
        cout << targetValue << " is not correct value." << endl;
      }
      return false;
    }
  }

  // x軸チェック
  for (int i = 0; i < FIELD_LENGTH; i++) {
    // 対象値と同じ座標はスキップ
    if (xOffset == i) {
      continue;
    }

    // 対象値と同じ値があった場合はfalseをreturn
    if (field[yOffset][i] == targetValue) {
      if (DEBUG_FLAG && DEBUG_DETAIL_FLAG) {
        cout << "checkValidationFunc:horizontal" << endl;
        cout << xOffset << ":" << yOffset << endl;
        cout << targetValue << " is not correct value." << endl;
      }
      return false;
    }
  }

  // 区域チェック
  int areaXOffset = xOffset / AREA_LENGTH;
  int areaYOffset = yOffset / AREA_LENGTH;
  for (int i = 0; i < AREA_LENGTH; i++) {
    for (int j = 0; j < AREA_LENGTH; j++) {
      if (DEBUG_FLAG && DEBUG_DETAIL_FLAG) {
          cout << "area check:" << endl << areaXOffset * AREA_LENGTH + j << ":" << areaYOffset * AREA_LENGTH + i << endl;
      }
        
      // 対象値と同じ座標はスキップ
      if (yOffset == (areaYOffset * AREA_LENGTH + i) && xOffset == (areaXOffset * AREA_LENGTH + j)) {
        continue;
      }

      // 対象値と同じ値があった場合はfalseをreturn
      if (field[areaYOffset * AREA_LENGTH + i][areaXOffset * AREA_LENGTH + j] == targetValue) {
        if (DEBUG_FLAG && DEBUG_DETAIL_FLAG) {
          cout << "checkValidationFunc:area" << endl;
          cout << xOffset << ":" << yOffset << endl;
          cout << targetValue << " is not correct value." << endl;
        }
        return false;
      }
    }
  }

  return true;
}

void printField(int field[FIELD_LENGTH][FIELD_LENGTH]) {
  cout << endl;
  for (int i = 0; i < FIELD_LENGTH; i++) {
    if (i != 0 && i % 3 == 0) {
        cout << "-----+-----+-----" << endl;
    }
    for(int j = 0; j < FIELD_LENGTH; j++) {
      if (j != 0) {
          if (j % 3 == 0) {
              cout << "|";
          } else {
              cout << " ";
          }
      }
      cout << field[i][j];
    }
    cout << endl;
  }
  return;
}