//vending_machine 프로그램 2111348 김재병

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

struct menu {     //품목 이름, 가격, 판매 횟수 저장할 구조체 정의
    char name[20];
    short cost, stock;
};  

struct menu item0; // 10개 품목의 전역 구조체 생성
struct menu item1;
struct menu item2;
struct menu item3;
struct menu item4;
struct menu item5;
struct menu item6;
struct menu item7;
struct menu item8;
struct menu item9;

//자판기 제목 출력 함수
void printTitle() {
    printf("=========================================\n");
    printf("|                 자판기                |\n");
    printf("=========================================\n");
}

// 사용자용 입력 key를 설명을 출력하는 함수
void printKeyExplain() { //사용자용 key 설명
    printf("ㅡㅡㅡㅡㅡㅡ 사용(key) 안내 ㅡㅡㅡㅡㅡㅡ\n");
    printf("▶▶ a<A> :  10원 동전 투입\n");
    printf("▶▶ s<S> :  50원 동전 투입\n");
    printf("▶▶ d<D> : 100원 동전 투입\n");
    printf("▶▶ f<F> : 500원 동전 투입\n");
    printf("-----------------------------------------\n");
    printf("▶▶ q<Q> : 구매\n");
    printf("▶▶ w<W> : 동전 반환\n");
    printf("▶▶ m<M> : 관리자 설정 열기\n");
    printf("-----------------------------------------\n");
    printf("▶▶ 0 : 프로그램 종료\n");
    printf("=========================================\n");
}

// 관리자용 입력 key를 설명하는 함수
void printAdminMenu() { //관리자용 key 설명
    printf("-----------------------------------------\n");
    printf("▶▶ z<Z> : 자판기 매출 조회\n");
    printf("▶▶ x<X> : 자판기 매출 초기화\n");
    printf("▶▶ c<C> : 판매 품목 금액 수정\n");
    printf("▶▶ v<V> : 판매 품목 재고 수정\n");
    printf("▶▶ r<R> : * 기본 상태로 초기화 *\n");
    printf("-----------------------------------------\n");
}

//"key를 입력하세요 : "를 출력하는 함수
void printEnterKey() {
    printf("▧ Key를 입력하세요 : ");
}

// 현재 투입된 금액을 출력하는 함수
void printCurrentAmount(int amount) {
    printf("=========================================\n");
    printf("     ▧ 현재 투입된 총 금액 : %d원 ▨ \n", amount);
    printf("=========================================\n");
}

// 상품 리스트를 출력하는 함수
void printItemLists() {
    printf("-----------------------------------------\n");
    printf("▶▶ 1번: %8s <<%5d원>> |재고: %2d|\n", item0.name, item0.cost, item0.stock);
    printf("▶▶ 2번: %8s <<%5d원>> |재고: %2d|\n", item1.name, item1.cost, item1.stock);
    printf("▶▶ 3번: %8s <<%5d원>> |재고: %2d|\n", item2.name, item2.cost, item2.stock);
    printf("▶▶ 4번: %8s <<%5d원>> |재고: %2d|\n", item3.name, item3.cost, item3.stock);
    printf("▶▶ 5번: %8s <<%5d원>> |재고: %2d|\n", item4.name, item4.cost, item4.stock);
    printf("▶▶ 6번: %8s <<%5d원>> |재고: %2d|\n", item5.name, item5.cost, item5.stock);
    printf("▶▶ 7번: %8s <<%5d원>> |재고: %2d|\n", item6.name, item6.cost, item6.stock);
    printf("▶▶ 8번: %8s <<%5d원>> |재고: %2d|\n", item7.name, item7.cost, item7.stock);
    printf("▶▶ 9번: %8s <<%5d원>> |재고: %2d|\n", item8.name, item8.cost, item8.stock);
    printf("▶▶10번: %8s <<%5d원>> |재고: %2d|\n", item9.name, item9.cost, item9.stock);
    printf("-----------------------------------------\n");
}

// 상품 리스트를 초기 설정으로 초기화하는 함수
void sysReset(int *amount, int *sales) {

    // 10개 품목 모두 기본값으로 초기화
    strcpy_s(item0.name, "핫식스");
    item0.cost = 1500;
    item0.stock = 10;
    strcpy_s(item1.name, "레쓰비");
    item1.cost = 500;
    item1.stock = 10;
    strcpy_s(item2.name, "몬스터");
    item2.cost = 2500;
    item2.stock = 10;
    strcpy_s(item3.name, "비타500");
    item3.cost = 1500;
    item3.stock = 10;
    strcpy_s(item4.name, "매실");
    item4.cost = 1000;
    item4.stock = 10;
    strcpy_s(item5.name, "사이다");
    item5.cost = 1000;
    item5.stock = 10;
    strcpy_s(item6.name, "콜라");
    item6.cost = 1200;
    item6.stock = 10;
    strcpy_s(item7.name, "제로콜라");
    item7.cost = 1200;
    item7.stock = 10;
    strcpy_s(item8.name, "환타");
    item8.cost = 1000;
    item8.stock = 10;
    strcpy_s(item9.name, "데자와");
    item9.cost = 1200;
    item9.stock = 10;
    *amount = 0;
    *sales = 0;
    //초기화 알림
    printf("\n      ▧ 시스템이 초기화되었습니다 ▨      \n\n");

}

// 구매할 품목을 입력받고 구매처리(재고, 매출)하는 함수
void buyItem(int* amount, int* sales) {

    printf("구매할 품목의 번호를 입력하세요 : ");
    short n;
    scanf(" %hd", &n);
    if (n < 1 || n > 10) { // 존재하지 않는 품목의 번호를 입력한 경우 경고문 출력 후 함수 종료
        printf("\n** 잘못된 입력값!! 올바른 번호를 입력해 주세요. **\n");
        printf("▧ 기본 메뉴로 이동합니다. ▧\n\n");
        return;
    }

    switch (n) { // 입력된 번호에 맞게 구매처리
    case 1:
        if (*amount - item0.cost <= 0)
            printf("\n       ※※ 금액이 부족합니다!! ※※\n\n");
        else if (item0.stock == 0)
            printf("\n       ※※ 재고가 부족합니다!! ※※\n\n");
        else {
            printf("\n구매가 완료되었습니다. 상품을 가져가세요.\n");
            printf("-----------------------------------------\n");
            *amount -= item0.cost;
            *sales += item0.cost;
            item0.stock--;
        }
        break;
    case 2:
        if (*amount - item1.cost < 0)
            printf("\n       ※※ 금액이 부족합니다!! ※※\n\n");
        else if (item1.stock == 0)
            printf("\n       ※※ 재고가 부족합니다!! ※※\n\n");
        else {
            printf("\n구매가 완료되었습니다. 상품을 가져가세요.\n");
            printf("-----------------------------------------\n");
            *amount -= item1.cost;
            *sales += item1.cost;
            item1.stock--;
        }
        break;
    case 3:
        if (*amount - item2.cost < 0)
            printf("\n       ※※ 금액이 부족합니다!! ※※\n\n");
        else if (item2.stock == 0)
            printf("\n       ※※ 재고가 부족합니다!! ※※\n\n");
        else {
            printf("\n구매가 완료되었습니다. 상품을 가져가세요.\n");
            printf("-----------------------------------------\n");
            *amount -= item2.cost;
            *sales += item2.cost;
            item2.stock--;
        }
        break;
    case 4:
        if (*amount - item3.cost < 0)
            printf("\n       ※※ 금액이 부족합니다!! ※※\n\n");
        else if (item3.stock == 0)
            printf("\n       ※※ 재고가 부족합니다!! ※※\n\n");
        else {
            printf("\n구매가 완료되었습니다. 상품을 가져가세요.\n");
            printf("-----------------------------------------\n");
            *amount -= item3.cost;
            *sales += item3.cost;
            item3.stock--;
        }
        break;
    case 5:
        if (*amount - item4.cost < 0)
            printf("\n       ※※ 금액이 부족합니다!! ※※\n\n");
        else if (item4.stock == 0)
            printf("\n       ※※ 재고가 부족합니다!! ※※\n\n");
        else {
            printf("\n구매가 완료되었습니다. 상품을 가져가세요.\n");
            printf("-----------------------------------------\n");
            *amount -= item4.cost;
            *sales += item4.cost;
            item4.stock--;
        }
        break;
    case 6:
        if (*amount - item5.cost < 0)
            printf("\n       ※※ 금액이 부족합니다!! ※※\n\n");
        else if (item5.stock == 0)
            printf("\n       ※※ 재고가 부족합니다!! ※※\n\n");
        else {
            printf("\n구매가 완료되었습니다. 상품을 가져가세요.\n");
            printf("-----------------------------------------\n");
            *amount -= item5.cost;
            *sales += item5.cost;
            item5.stock--;
        }
        break;
    case 7:
        if (*amount - item6.cost < 0)
            printf("\n       ※※ 금액이 부족합니다!! ※※\n\n");
        else if (item6.stock == 0)
            printf("\n       ※※ 재고가 부족합니다!! ※※\n\n");
        else {
            printf("\n구매가 완료되었습니다. 상품을 가져가세요.\n");
            printf("-----------------------------------------\n");
            *amount -= item6.cost;
            *sales += item6.cost;
            item6.stock--;
        }
        break;
    case 8:
        if (*amount - item7.cost < 0)
            printf("\n       ※※ 금액이 부족합니다!! ※※\n\n");
        else if (item7.stock == 0)
            printf("\n       ※※ 재고가 부족합니다!! ※※\n\n");
        else {
            printf("\n구매가 완료되었습니다. 상품을 가져가세요.\n");
            printf("-----------------------------------------\n");
            *amount -= item7.cost;
            *sales += item7.cost;
            item7.stock--;
        }
        break;
    case 9:
        if (*amount - item8.cost < 0)
            printf("\n       ※※ 금액이 부족합니다!! ※※\n\n");
        else if (item8.stock == 0)
            printf("\n       ※※ 재고가 부족합니다!! ※※\n\n");
        else {
            printf("\n구매가 완료되었습니다. 상품을 가져가세요.\n");
            printf("-----------------------------------------\n");
            *amount -= item8.cost;
            *sales += item8.cost;
            item8.stock--;
        }
        break;
    case 10:
        if (*amount - item9.cost < 0)
            printf("\n       ※※ 금액이 부족합니다!! ※※\n\n");
        else if (item9.stock == 0)
            printf("\n       ※※ 재고가 부족합니다!! ※※\n\n");
        else {
            printf("\n구매가 완료되었습니다. 상품을 가져가세요.\n");
            printf("-----------------------------------------\n");
            *amount -= item9.cost;
            *sales += item9.cost;
            item9.stock--;
        }
        break;
    }
}

// 상품의 가격을 수정하는 함수
void changeItemCost() {

    short num1, num2; //번호와 금액을 저장할 변수 선언

    for (num1 = 0; num1 == 0;) {

        printf("\n▧ 수정할 품목의 번호를 입력하세요 : ");
        scanf(" %hd", &num1);

        if (num1 < 1 || num1 > 10) { // 품목 번호가 존재하지 않을 경우 경고문 출력 후 함수 종료
            printf("\n** 잘못된 입력값!! 올바른 번호를 입력해 주세요. **\n\n");
            printf("      ▧ 기본 메뉴로 이동합니다. ▧\n\n");
            break;
        }

        printf("※※ 금액은 30,000원을 넘길 수 없습니다! ※※\n");
        printf("▧ 수정할 품목의 금액를 입력하세요 : ");
        scanf(" %hd", &num2);
        printf("\n");

        if (num2 % 10 > 0 || num2 > 30000) { // 지정 금액을 넘길 경우 경고문 출력 후 함수 종료
            printf("\n** 잘못된 입력값!! **\n");
            printf("** 최소 금액은 10원이며\n");
            printf("금액을 10으로 나누었을때\n나머지는 0이어야 합니다. **\n\n");
            printf("       ▧ 기본 메뉴로 이동합니다. ▧\n\n");
            break;
        }

        switch (num1) { // 각 번호에 맞게 금액 변경 후 결과 출력
        case 1:
            printf("수정된 품목 : %s => %d원\n\n", item0.name, num2);
            item0.cost = num2;
            break;
        case 2:
            printf("수정된 품목 : %s => %d원\n\n", item1.name, num2);
            item1.cost = num2;
            break;
        case 3:
            printf("수정된 품목 : %s => %d원\n\n", item2.name, num2);
            item2.cost = num2;
            break;
        case 4:
            printf("수정된 품목 : %s => %d원\n\n", item3.name, num2);
            item3.cost = num2;
            break;
        case 5:
            printf("수정된 품목 : %s => %d원\n\n", item4.name, num2);
            item4.cost = num2;
            break;
        case 6:
            printf("수정된 품목 : %s => %d원\n\n", item5.name, num2);
            item5.cost = num2;
            break;
        case 7:
            printf("수정된 품목 : %s => %d원\n\n", item6.name, num2);
            item6.cost = num2;
            break;
        case 8:
            printf("수정된 품목 : %s => %d원\n\n", item7.name, num2);
            item7.cost = num2;
            break;
        case 9:
            printf("수정된 품목 : %s => %d원\n\n", item8.name, num2);
            item8.cost = num2;
            break;
        case 10:
            printf("수정된 품목 : %s => %d원\n\n", item9.name, num2);
            item9.cost = num2;
            break;
        }
    }
}

// 상품의 재고를 수정하는 함수
void changeItemStock() {

    short num1, num2; //번호와 재고를 저장할 변수 선언

    for (num1 = 0; num1 == 0;) {

        printf("\n▧ 수정할 품목의 번호를 입력하세요 : ");
        scanf(" %hd", &num1);

        if (num1 < 1 || num1 > 10) { // 품목 번호가 존재하지 않을 경우 경고문 출력 후 함수 종료
            printf("\n** 잘못된 입력값!! 올바른 번호를 입력해 주세요. **\n");
            printf("▧ 기본 메뉴로 이동합니다. ▧\n\n");
            break;
        }

        printf("\n▧ 수정할 품목의 재고를 입력하세요 : ");
        scanf(" %hd", &num2);
        printf("\n");

        if (num2 < 0 || num2 > 10) { // 지정 재고 수를 넘길 경우 경고문 출력 후 함수 종료
            printf("\n** 잘못된 입력값!! 올바른 수량을 입력해 주세요. **\n");
            printf("▧ 기본 메뉴로 이동합니다. ▧\n\n");
            break;
        }

        switch (num1) { // 각 번호에 맞게 재고 변경 후 결과 출력
        case 1:
            printf("수정된 품목 : %s => %d개\n", item0.name, num2);
            item0.stock = num2;
            break;
        case 2:
            printf("수정된 품목 : %s => %d원\n", item1.name, num2);
            item1.stock = num2;
            break;
        case 3:
            printf("수정된 품목 : %s => %d원\n", item2.name, num2);
            item2.stock = num2;
            break;
        case 4:
            printf("수정된 품목 : %s => %d원\n", item3.name, num2);
            item3.stock = num2;
            break;
        case 5:
            printf("수정된 품목 : %s => %d원\n", item4.name, num2);
            item4.stock = num2;
            break;
        case 6:
            printf("수정된 품목 : %s => %d원\n", item5.name, num2);
            item5.stock = num2;
            break;
        case 7:
            printf("수정된 품목 : %s => %d원\n", item6.name, num2);
            item6.stock = num2;
            break;
        case 8:
            printf("수정된 품목 : %s => %d원\n", item7.name, num2);
            item7.stock = num2;
            break;
        case 9:
            printf("수정된 품목 : %s => %d원\n", item8.name, num2);
            item8.stock = num2;
            break;
        case 10:
            printf("수정된 품목 : %s => %d원\n", item9.name, num2);
            item9.stock = num2;
            break;
        }
    }
}

int main(void) {

    /*
    main 함수 안에서는 위에서 선언한 함수를 이용해 전체적인 UI를 출력하고
    입력받은 문자에 따라 key설명에 따른 switch case문을 이용하여 각각의 기능을 수행.
    동전 투입은 반복적인 작업이기 때문에 불필요하게 전체 UI를 출력X
    동전 투입 이외의 기능을 수행한 뒤 전체 UI를 출력하여 보여줌.
    */

    int amount = 0, sales = 0; //amouont는 현재 입된 금, sales는 현재 매

    char key = 't';

    printTitle();               // 자판기 제목 출력
    sysReset(&amount, &sales);                 // 시스템 초기화 후 안내문 출력
    printItemLists();           // 판매품목 출력
    printCurrentAmount(amount); // 입력된 금액 출력
    printKeyExplain();          // 입력 key에 대한 설명 출력

    for (int i = 0; key != '0'; i++) {

        if (i != 0 && key != 'A' && key != 'S' && key != 'D' && key != 'F')
        {   // 동전을 투입하지 않고 다른 키를 입력하였을 때 전체 UI 출력
            printTitle();
            printItemLists();
            printCurrentAmount(amount);
            printKeyExplain();
        }

        printEnterKey();
        scanf(" %c", &key);

        //소문자로 입력 시 대문자로 변경
        if (key >= 'a' && key <= 'z')
            key -= 32;


        // 입력 받은 문자에 따라 각 기능 수행
        switch (key) {
        case 'A': // 10원 입력
            amount += 10;
            printCurrentAmount(amount);
            break;

        case 'S': // 50원 입력
            amount += 50;
            printCurrentAmount(amount);
            break;

        case 'D': // 100원 입력
            amount += 100;
            printCurrentAmount(amount);
            break;

        case 'F': // 500원 입력
            amount += 500;
            printCurrentAmount(amount);
            break;

        case 'Q': // 물품 구매하기

            printItemLists();
            buyItem(&amount, &sales);

            break;

        case 'W': // 동전 반환
            if (amount == 0) {
                printf("\n       ※※ 투입된 금액이 없습니다! ※※\n\n");
                break;
            }
            else {
                amount = 0;
                printf("\n       ※※ 동전이 반환되었습니다. ※※\n\n");
                printCurrentAmount(amount);
                break;
            }

        case 'M': // 관리자 설정 열기
            printAdminMenu();  // 관리자용 key설명 출력
            printEnterKey();

            char adminKey;

            scanf(" %c", &adminKey);

            // 소문자를 입력 시 대문자로 변경
            if (adminKey >= 'a' && adminKey <= 'z')
                adminKey -= 32;

            switch (adminKey) { // 관리자 설정 전용 메뉴에 따른 case 분류

            case 'Z': // 매출 조회
                printf("\n- 매출 총액 : %d원\n", sales);
                printf("▧ 기본 메뉴로 이동합니다. ▧\n\n");
                break;

            case 'X': // 매출 초기화
                printf("▧ 매출이 초기화 되었습니다. ▧\n");
                printf("▧ 기본 메뉴로 이동합니다. ▧\n\n");
                sales = 0;
                break;

            case 'C': // 품목 금액 수정
                changeItemCost();
                break;

            case 'V': // 품목 재고 수정
                changeItemStock();
                break;
            case 'R': // 판매 품목 기본 상태로 초기화
                sysReset(&amount, &sales);
                break;

            default:
                printf("\n** 잘못된 입력값!! 올바른 Key를 입력해 주세요. **\n\n");
                break;
            }
            break;

        case '0': // 자판기 프로그램 종료

            //경고문 출력
            printf("\n종료시 수정된 데이터는 초기값으로 초기화됩니다.");
            printf("\n자판기 프로그램을 종료하시겠습니까?\nY / N : ");

            char selectOff;
            scanf(" %c", &selectOff);

            if (selectOff == 'Y' || selectOff == 'y') { //Y(y) 입력시 자판기 종료
                printf("\n자판기를 종료합니다.\n");
                break;
            }

            else if (selectOff == 'N' || selectOff == 'n') { //N(n) 입력시 실행 취소
                printf("       ※※ 실행을 취소합니다. ※※\n\n");
                key = '.'; // 전체 반복문이 종료되지 않게 key값 임의 변경
                break;
            }

            else { //Y(y), N(n) 이외의 문자 입력 시 경고문 출력 후 실행 취소
                printf("\n** 잘못된 입력값!! 올바른 Key를 입력해 주세요. **\n");
                printf("       ※※ 실행을 취소합니다. ※※\n\n");
                key = '.'; // 전체 반복문이 종료되지 않게 key값 임의 변경
                break;
            }

        default:
            printf("\n** 잘못된 입력값!! 올바른 Key를 입력해 주세요. **\n\n");
            break;
        }
    }

    return 0;
}