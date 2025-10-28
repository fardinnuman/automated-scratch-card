#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_USERS_179 1000
#define MAX_CARDS_179 2000

#define ADMIN_USER_179 "admin"
#define ADMIN_PASS_179 "admin123"

struct UserCred_179 {
    char mobile_179[20];
};

struct UserCred_179 systemUsers_179[] = {
    {"01406369675"},
    {"01406369676"},
    {"01406369677"},
    {"01406369678"},
    {"01406369679"},
    {"01406369680"}
};
int systemUserCount_179 = 6;

struct User_179 {
    char mobile_179[20];
    int minutes_179;
    int attempts_179;
    int locked_179;
};

struct Card_179 {
    char number_179[25];
    int minutes_179;
    int price_179;
    int used_179;
};

void generateCardNumber_179(char *num_179);

struct User_179 users_179[MAX_USERS_179];
struct Card_179 cards_179[MAX_CARDS_179];
int userCount_179 = 0, cardCount_179 = 0;

void saveUsers_179() {
    FILE *fp = fopen("users.txt", "w");
    for (int i = 0; i < userCount_179; i++) {
        fprintf(fp, "%s %d %d %d\n", users_179[i].mobile_179, users_179[i].minutes_179,
                users_179[i].attempts_179, users_179[i].locked_179);
    }
    fclose(fp);
}

void loadUsers_179() {
    FILE *fp = fopen("users.txt", "r");
    if (!fp) return;
    while (fscanf(fp, "%s %d %d %d", users_179[userCount_179].mobile_179,
                  &users_179[userCount_179].minutes_179,
                  &users_179[userCount_179].attempts_179,
                  &users_179[userCount_179].locked_179) == 4) {
        userCount_179++;
    }
    fclose(fp);
}

void saveCards_179() {
    FILE *fp = fopen("cards.txt", "w");
    for (int i = 0; i < cardCount_179; i++) {
        fprintf(fp, "%s %d %d %d\n", cards_179[i].number_179, cards_179[i].minutes_179,
                cards_179[i].price_179, cards_179[i].used_179);
    }
    fclose(fp);
}

void loadCards_179() {
    FILE *fp = fopen("cards.txt", "r");
    if (!fp) {
        int minutesArray_179[] = {40, 60, 100};
        int priceArray_179[] = {50, 70, 120};

        for (int i = 0; i < 1000; i++) {
            struct Card_179 newCard_179;
            generateCardNumber_179(newCard_179.number_179);
            int idx = rand() % 3;
            newCard_179.minutes_179 = minutesArray_179[idx];
            newCard_179.price_179 = priceArray_179[idx];
            newCard_179.used_179 = 0;
            cards_179[cardCount_179++] = newCard_179;
        }
        saveCards_179();
        return;
    }

    while (fscanf(fp, "%s %d %d %d", cards_179[cardCount_179].number_179,
                  &cards_179[cardCount_179].minutes_179,
                  &cards_179[cardCount_179].price_179,
                  &cards_179[cardCount_179].used_179) == 4) {
        cardCount_179++;
    }
    fclose(fp);
}

void addHistory_179(const char *mobile_179, const char *card_179, int minutes_179) {
    FILE *fp = fopen("history.txt", "a");
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);

    fprintf(fp, "%s %02d/%02d/%04d %02d:%02d %d %s\n",
            card_179,
            tm->tm_mday, tm->tm_mon + 1, tm->tm_year + 1900,
            tm->tm_hour, tm->tm_min,
            minutes_179,
            mobile_179);
    fclose(fp);
}

void generateCardNumber_179(char *num_179) {
    for (int i = 0; i < 20; i++)
        num_179[i] = '0' + rand() % 10;
    num_179[20] = '\0';
}

struct User_179* getUser_179(const char *mobile_179) {
    for (int i = 0; i < userCount_179; i++) {
        if (strcmp(users_179[i].mobile_179, mobile_179) == 0)
            return &users_179[i];
    }
    strcpy(users_179[userCount_179].mobile_179, mobile_179);
    users_179[userCount_179].minutes_179 = 0;
    users_179[userCount_179].attempts_179 = 0;
    users_179[userCount_179].locked_179 = 0;
    userCount_179++;
    return &users_179[userCount_179 - 1];
}

struct Card_179* getCard_179(const char *num_179) {
    for (int i = 0; i < cardCount_179; i++) {
        if (strcmp(cards_179[i].number_179, num_179) == 0)
            return &cards_179[i];
    }
    return NULL;
}

void userMenu_179() {
    char mobile_179[20], cardnum_179[25];

    printf("Enter Mobile Number: ");
    scanf("%s", mobile_179);

    struct User_179 *user_179 = getUser_179(mobile_179);

    if (user_179->locked_179) {
        printf("Your account is locked. Contact admin\n");
        return;
    }

    printf("Enter Card Number: ");
    scanf("%s", cardnum_179);

    struct Card_179 *card_179 = getCard_179(cardnum_179);
    if (!card_179 || card_179->used_179) {
        user_179->attempts_179++;
        printf("Invalid or already used card!\n");
        if (user_179->attempts_179 >= 3) {
            user_179->locked_179 = 1;
            printf("Account locked after 3 invalid attempts\n");
        }
        saveUsers_179();
        return;
    }

    user_179->minutes_179 += card_179->minutes_179;
    card_179->used_179 = 1;
    user_179->attempts_179 = 0;
    printf("Reload Successful\n");
    addHistory_179(mobile_179, cardnum_179, card_179->minutes_179);

    saveUsers_179();
    saveCards_179();

    struct Card_179 newCard_179;
    generateCardNumber_179(newCard_179.number_179);
    newCard_179.minutes_179 = card_179->minutes_179;
    if (newCard_179.minutes_179 == 40) newCard_179.price_179 = 50;
    else if (newCard_179.minutes_179 == 60) newCard_179.price_179 = 70;
    else if (newCard_179.minutes_179 == 100) newCard_179.price_179 = 120;
    else newCard_179.price_179 = 0;
    newCard_179.used_179 = 0;
    cards_179[cardCount_179++] = newCard_179;
}

// Search option
void searchMenu_179() {
    char searchMobile_179[20];
    printf("Enter Mobile Number: ");
    scanf("%s", searchMobile_179);

    FILE *fp = fopen("history.txt", "r");
    if (!fp) {
        printf("No history found\n");
        return;
    }

    char cardNo_179[25], mobile_179[20];
    int minutes_179, day, month, year, hour, min;

    printf("\nCard No              Date       Time  Minute\n");

    int totalTransactions = 0;
    while (fscanf(fp, "%s %d/%d/%d %d:%d %d %s\n",
                  cardNo_179, &day, &month, &year, &hour, &min, &minutes_179, mobile_179) == 8) {
        if (strcmp(mobile_179, searchMobile_179) == 0) {
            printf("%-20s %02d/%02d/%04d %02d:%02d %-6d\n",
                   cardNo_179, day, month, year, hour, min, minutes_179);
            totalTransactions++;
        }
    }
    printf("Total Transactions: %d\n", totalTransactions);

    fclose(fp);
}

// Admin menu
void adminMenu_179() {
    int choice_179;
    char mobile_179[20], cardnum_179[25];
    while (1) {
        printf("\n--- Admin Menu ---\n");
        printf("1. New Card\n2. Delete Card\n3. Unlock Card\n4. History\n5. Statistics\n6. Search\n7. Exit\n");
        printf("Enter your option: ");
        scanf("%d", &choice_179);
        // New Card option
        if (choice_179 == 1) {
            int numCards_179, minutes_179, price_179;
            printf("How many cards and minute: ");
            scanf("%d %d", &numCards_179, &minutes_179);
            if (minutes_179 == 40) price_179 = 50;
            else if (minutes_179 == 60) price_179 = 70;
            else if (minutes_179 == 100) price_179 = 120;
            else price_179 = 0;

            for (int i = 0; i < numCards_179; i++) {
                struct Card_179 newCard_179;
                generateCardNumber_179(newCard_179.number_179);
                newCard_179.minutes_179 = minutes_179;
                newCard_179.price_179 = price_179;
                newCard_179.used_179 = 0;
                cards_179[cardCount_179++] = newCard_179;
            }
            printf("%d Cards Creation Successful\n", numCards_179);
            saveCards_179();
        }
        // Delete Card option
        else if (choice_179 == 2) {
            printf("Enter Card Number: ");
            scanf("%s", cardnum_179);
            int found_179 = 0;
            for (int i = 0; i < cardCount_179; i++) {
                if (strcmp(cards_179[i].number_179, cardnum_179) == 0) {
                    for (int j = i; j < cardCount_179 - 1; j++)
                        cards_179[j] = cards_179[j + 1];
                    cardCount_179--;
                    found_179 = 1;
                    printf("Card Deletion Successful\n");
                    saveCards_179();
                    break;
                }
            }
            if (!found_179) printf("Card not found\n");
        }
        // Unlock Card option
        else if (choice_179 == 3) {
            printf("Enter Mobile Number: ");
            scanf("%s", mobile_179);
            struct User_179 *u = getUser_179(mobile_179);
            u->locked_179 = 0;
            u->attempts_179 = 0;
            printf("Card Unlock Successful\n");
            saveUsers_179();
        }
        // History option
        else if (choice_179 == 4) {
            FILE *fp = fopen("history.txt", "r");
            if (!fp) { printf("No history found\n"); continue; }
            char cardNo_179[25], mobile_179[20];
            int minutes_179, day, month, year, hour, min;

            printf("\nCard No              Date       Time  Minute Mobile No\n");

            while (fscanf(fp, "%s %d/%d/%d %d:%d %d %s\n",
                          cardNo_179, &day, &month, &year, &hour, &min, &minutes_179, mobile_179) == 8) {
                printf("%-20s %02d/%02d/%04d %02d:%02d %-6d %-15s\n",
                       cardNo_179, day, month, year, hour, min, minutes_179, mobile_179);
            }
            fclose(fp);
        }
        // Statistics option
        else if (choice_179 == 5) {
            int sold40_179 = 0, sold60_179 = 0, sold100_179 = 0;
            int remain40_179 = 0, remain60_179 = 0, remain100_179 = 0;
            int amount40_179 = 0, amount60_179 = 0, amount100_179 = 0;

            for (int i = 0; i < cardCount_179; i++) {
                if (cards_179[i].minutes_179 == 40) {
                    if (cards_179[i].used_179) { sold40_179++; amount40_179 += cards_179[i].price_179; }
                    else remain40_179++;
                } else if (cards_179[i].minutes_179 == 60) {
                    if (cards_179[i].used_179) { sold60_179++; amount60_179 += cards_179[i].price_179; }
                    else remain60_179++;
                } else if (cards_179[i].minutes_179 == 100) {
                    if (cards_179[i].used_179) { sold100_179++; amount100_179 += cards_179[i].price_179; }
                    else remain100_179++;
                }
            }

            printf("\nTotal Cards Sold:  40 min:%d  60 min:%d  100 min:%d\n", sold40_179, sold60_179, sold100_179);
            printf("Total Cards Remains:  40 min:%d  60 min:%d  100 min:%d\n", remain40_179, remain60_179, remain100_179);
            printf("Total Amounts Sold in Tk.:  40 min:%d  60 min:%d  100 min:%d\n", amount40_179, amount60_179, amount100_179);
        }

        else if (choice_179 == 6) searchMenu_179();
        else if (choice_179 == 7) break;
        else printf("Invalid option!\n");
    }
}

int login(char *role_179) {
    char input[20];
    printf("~~~~~ Login Panel ~~~~~\n");
    printf("Enter Login(admin/user): ");
    scanf(" %19s", input);

    // Admin login
    if (strcmp(input, ADMIN_USER_179) == 0) {
        char pass[20];
        printf("Enter Password: ");
        scanf(" %19s", pass);
        if (strcmp(pass, ADMIN_PASS_179) == 0) {
            strcpy(role_179, "admin");
            return 1;
        }
        return 0;
    }

    // User login
    if (strcmp(input, "user") == 0) {
        strcpy(role_179, "user");
        return 1;
    }

    return 0;
}

// Main function
int main() {

    printf("Submitted by:\nFardin Bin Aslam Numan\nRoll: 2403179\nSection: C\n\n");
    printf("• To log in as admin, enter 'admin' and 'admin123' as the credentials\n");
    printf("• To log in as user, enter 'user' and then mobile number\n\n");

    srand(time(NULL));
    loadUsers_179();
    loadCards_179();

    char role_179[10];

    while (1) {
        if (!login(role_179)) {
            printf("Invalid login. Try again\n\n");
            continue;
        }

        if (strcmp(role_179, "admin") == 0)
            adminMenu_179();
        else
            userMenu_179();
    }

    saveUsers_179();
    saveCards_179();
    return 0;
}
