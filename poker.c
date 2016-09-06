#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define CARD_NUM 5
#define STACK 52
#define SHUFFLE_MAX 200

// 関数のプロトタイプ宣言
void shuffle(int cardStack[]);
void cardInit(int myCard[], int cardStack[]);
void display(int myCard[]);
char* getSuit(int card);
char* getNumber(int card);
void cardChange(int myCard[], int cardStack[]);
void judge(int myCard[]);

int main() {
    // 山札
    int cardStack[STACK];

    // 手札
    int myCard[CARD_NUM];

    // カードの初期化
    cardInit(myCard, cardStack);

    printf("*ドローポーカー*\n");

    // カードの表示
    display(myCard);

    // カードの交換
    cardChange(myCard, cardStack);

    // カードの表示
    display(myCard);

    // 判定
    judge(myCard);

    return 0;
}

// カードの初期化とシャッフル
void shuffle(int cardStack[]) {
    for (int i = 0; i < STACK; i++) {
        cardStack[i] = i;
    }
    for (int j = 0; j < SHUFFLE_MAX; j++) {
        // 0~51までの乱数を取得
        int a = rand() % STACK;
        int b = rand() % STACK;
        // 配列のa番目とb番目の値をスワップ
        int temp = cardStack[a];
        cardStack[a] = cardStack[b];
        cardStack[b] = temp;
    }
}

// 手札の初期化
void cardInit(int myCard[], int cardStack[]) {
    // 乱数の初期化
    srand((unsigned)time(NULL));

    shuffle(cardStack);
    for (int i = 0; i < CARD_NUM; i++) {
        myCard[i] = cardStack[i];
    }
}

// カードの交換
void cardChange(int myCard[], int cardStack[]) {
    char buf = 0;
    for (int i = 0; i < CARD_NUM; i++) {
        printf("%d枚目のカードは交換しますか? [y/n]\n", i + 1);
        scanf(" %c", &buf);
        if (buf == 'y') {
            myCard[i] = cardStack[CARD_NUM + i];
        }
    }
}

// カードの表示
void display(int myCard[]) {
    for (int i = 0; i < CARD_NUM; i++) {
        printf("[%s %s]", getSuit(myCard[i]), getNumber(myCard[i]));
    }
    printf("\n");
}

// 役判定
void judge(int myCard[]) {
    // 数字の個数
    int num[13] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    // スートの個数
    int suit[4] = {0, 0, 0, 0};

    for (int i = 0; i < CARD_NUM; i++) {
        num[myCard[i] % 13]++;
        suit[myCard[i] / 13]++;
    }

    // フラッシュかどうか
    int flash = 0;
    for (int i = 0; i < 4; i++) {
        if (suit[i] == 4) flash = 1;
    }

    // ストレートかどうか
    int straight = 0;
    for (int i = 0; i <= 8; i++) {
        if (num[i] == 1 && num[i+1] == 1 && num[i+2] == 1 && num[i+3] == 1 && num[i+4] == 1) {
            straight = 1;
        }
    }

    // A, K, Q, J, 10 の場合
    // (ロイヤルの判定)
    int royal = 0;
    if (num[0] == 1 && num[12] == 1 && num[11] == 1 && num[10] == 1 && num[9] == 1) {
            straight = 1;
            royal = 1;
    }

    // 同じカードの枚数の最大値
    int card = 0;
    for (int i = 0; i < 13; i++) {
        if (card < num[i]) card = num[i];
    }

    // ペアの個数
    int pair = 0;
    for (int i = 0; i < 13; i++) {
        if (num[i] == 2) pair++;
    }

    // 判定
    // ロイヤルストレートフラッシュ
    if (royal == 1 && straight == 1 && flash == 1) {
        printf("ロイヤルストレートフラッシュ\n");
        return;
    }

    // ストレートフラッシュ
    if (straight == 1 && flash == 1) {
        printf("ストレートフラッシュ\n");
        return;
    }

    // 4カード
    if (card == 4) {
        printf("4カード\n");
        return;
    }

    // フルハウス
    if (card == 3 && pair == 1) {
        printf("フルハウス\n");
        return;
    }

    // フラッシュ
    if (flash == 1) {
        printf("フラッシュ\n");
        return;
    }

    // ストレート
    if (straight == 1) {
        printf("ストレート\n");
        return;
    }

    // 3カード
    if (card == 3) {
        printf("3カード\n");
        return;
    }

    // 2ペア
    if (pair == 2) {
        printf("2ペア\n");
        return;
    }

    // 1ペア
    if (pair == 1) {
        printf("1ペア\n");
        return;
    }

    // ノーペア
    printf("ノーペア\n");

}

// カードの数字
char* getNumber(int card) {
    int num = card % 13;
    switch(num) {
        case 0:
            return "A";
        case 1:
            return "2";
        case 2:
            return "3";
        case 3:
            return "4";
        case 4:
            return "5";
        case 5:
            return "6";
        case 6:
            return "7";
        case 7:
            return "8";
        case 8:
            return "9";
        case 9:
            return "10";
        case 10:
            return "J";
        case 11:
            return "Q";
        case 12:
            return "K";
        default:
            return "";
    }
}

// カードのスート
char* getSuit(int card) {
    if (0 <= card && card <= 12) {
        return "S";
    } else if (13 <= card && card <= 25) {
        return "C";
    } else if (26 <= card && card <= 38) {
        return "D";
    } else if (39 <= card && card <= 51) {
        return "H";
    }
}
