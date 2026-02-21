#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

struct Entry {
    char name[50];
    int calories;
    int protein;
};

struct Entry food[MAX];
int count = 0;
int calorieGoal = 2500;
int workoutBurn = 0;

/* Function Prototypes */
void addFood();
void addWorkout();
void viewSummary();
void bmiCalculator();
void saveToFile(char date[]);
void loadFromFile(char date[]);
void weeklyReport();

int totalCalories();
int totalProtein();

int main() {
    int choice;
    char date[20];

    printf("Enter today's date (YYYY-MM-DD): ");
    scanf("%s", date);

    loadFromFile(date);

    while (1) {
        printf("\n====== ADVANCED FITNESS TRACKER ======\n");
        printf("1. Add Food\n");
        printf("2. Add Workout (Calories Burned)\n");
        printf("3. View Daily Summary\n");
        printf("4. BMI Calculator\n");
        printf("5. Weekly Report\n");
        printf("6. Save & Exit\n");
        printf("Choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: addFood(); break;
            case 2: addWorkout(); break;
            case 3: viewSummary(); break;
            case 4: bmiCalculator(); break;
            case 5: weeklyReport(); break;
            case 6:
                saveToFile(date);
                printf("Data saved. Stay shredded 💪\n");
                exit(0);
            default:
                printf("Invalid option!\n");
        }
    }
}

/* Add Food */
void addFood() {
    if (count >= MAX) return;

    printf("Food name: ");
    scanf(" %[^\n]", food[count].name);

    printf("Calories: ");
    scanf("%d", &food[count].calories);

    printf("Protein (g): ");
    scanf("%d", &food[count].protein);

    count++;
}

/* Add Workout */
void addWorkout() {
    int burn;
    printf("Calories burned in workout: ");
    scanf("%d", &burn);
    workoutBurn += burn;
}

/* Total Calories */
int totalCalories() {
    int sum = 0;
    for (int i = 0; i < count; i++)
        sum += food[i].calories;
    return sum;
}

/* Total Protein */
int totalProtein() {
    int sum = 0;
    for (int i = 0; i < count; i++)
        sum += food[i].protein;
    return sum;
}

/* View Summary */
void viewSummary() {
    int intake = totalCalories();
    int net = intake - workoutBurn;

    printf("\n--- DAILY SUMMARY ---\n");
    printf("Total Calories: %d kcal\n", intake);
    printf("Workout Burned: %d kcal\n", workoutBurn);
    printf("Net Calories: %d kcal\n", net);
    printf("Total Protein: %d g\n", totalProtein());
    printf("Calorie Goal: %d kcal\n", calorieGoal);
    printf("Remaining: %d kcal\n", calorieGoal - net);
}

/* BMI Calculator */
void bmiCalculator() {
    float weight, height, bmi;

    printf("Enter weight (kg): ");
    scanf("%f", &weight);

    printf("Enter height (m): ");
    scanf("%f", &height);

    bmi = weight / (height * height);

    printf("Your BMI: %.2f\n", bmi);

    if (bmi < 18.5)
        printf("Underweight\n");
    else if (bmi < 25)
        printf("Normal\n");
    else if (bmi < 30)
        printf("Overweight\n");
    else
        printf("Obese\n");
}

/* Save Data */
void saveToFile(char date[]) {
    char filename[30];
    sprintf(filename, "%s.txt", date);

    FILE *fp = fopen(filename, "w");
    if (fp == NULL) return;

    fprintf(fp, "%d %d\n", count, workoutBurn);

    for (int i = 0; i < count; i++)
        fprintf(fp, "%s %d %d\n",
                food[i].name,
                food[i].calories,
                food[i].protein);

    fclose(fp);
}

/* Load Data */
void loadFromFile(char date[]) {
    char filename[30];
    sprintf(filename, "%s.txt", date);

    FILE *fp = fopen(filename, "r");
    if (fp == NULL) return;

    fscanf(fp, "%d %d", &count, &workoutBurn);

    for (int i = 0; i < count; i++)
        fscanf(fp, " %[^\n] %d %d",
               food[i].name,
               &food[i].calories,
               &food[i].protein);

    fclose(fp);
}

/* Weekly Report */
void weeklyReport() {
    char date[20];
    char filename[30];
    int weeklyCalories = 0;
    int weeklyProtein = 0;

    printf("Enter 7 dates (YYYY-MM-DD):\n");

    for (int i = 0; i < 7; i++) {
        printf("Date %d: ", i + 1);
        scanf("%s", date);

        sprintf(filename, "%s.txt", date);
        FILE *fp = fopen(filename, "r");

        if (fp == NULL) {
            printf("No data for %s\n", date);
            continue;
        }

        int c, w;
        fscanf(fp, "%d %d", &c, &w);

        int tempCal = 0, tempProt = 0;
        for (int j = 0; j < c; j++) {
            char name[50];
            int cal, prot;
            fscanf(fp, " %[^\n] %d %d", name, &cal, &prot);
            tempCal += cal;
            tempProt += prot;
        }

        weeklyCalories += tempCal;
        weeklyProtein += tempProt;

        fclose(fp);
    }

    printf("\n--- WEEKLY REPORT ---\n");
    printf("Total Weekly Calories: %d kcal\n", weeklyCalories);
    printf("Average Per Day: %d kcal\n", weeklyCalories / 7);
    printf("Total Weekly Protein: %d g\n", weeklyProtein);
    printf("Average Protein Per Day: %d g\n", weeklyProtein / 7);
}
