#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

#define MAX 100

struct Entry {
    string name;
    int calories;
    int protein;
};

vector<Entry> food;
int calorieGoal = 2500;
int workoutBurn = 0;

/* Function Prototypes */
void addFood();
void addWorkout();
void viewSummary();
void bmiCalculator();
void saveToFile(string date);
void loadFromFile(string date);
void weeklyReport();

int totalCalories();
int totalProtein();

int main() {
    int choice;
    string date;

    cout << "Enter today's date (YYYY-MM-DD): ";
    cin >> date;

    loadFromFile(date);

    while (true) {
        cout << "\n====== ADVANCED FITNESS TRACKER ======\n";
        cout << "1. Add Food\n";
        cout << "2. Add Workout (Calories Burned)\n";
        cout << "3. View Daily Summary\n";
        cout << "4. BMI Calculator\n";
        cout << "5. Weekly Report\n";
        cout << "6. Save & Exit\n";
        cout << "Choice: ";
        cin >> choice;

        switch(choice) {
            case 1: addFood(); break;
            case 2: addWorkout(); break;
            case 3: viewSummary(); break;
            case 4: bmiCalculator(); break;
            case 5: weeklyReport(); break;
            case 6:
                saveToFile(date);
                cout << "Data saved. Stay shredded 💪\n";
                return 0;
            default:
                cout << "Invalid option!\n";
        }
    }
}

/* Add Food */
void addFood() {
    if (food.size() >= MAX) return;

    Entry e;

    cin.ignore();
    cout << "Food name: ";
    getline(cin, e.name);

    cout << "Calories: ";
    cin >> e.calories;

    cout << "Protein (g): ";
    cin >> e.protein;

    food.push_back(e);
}

/* Add Workout */
void addWorkout() {
    int burn;
    cout << "Calories burned in workout: ";
    cin >> burn;
    workoutBurn += burn;
}

/* Total Calories */
int totalCalories() {
    int sum = 0;
    for (const auto &e : food)
        sum += e.calories;
    return sum;
}

/* Total Protein */
int totalProtein() {
    int sum = 0;
    for (const auto &e : food)
        sum += e.protein;
    return sum;
}

/* View Summary */
void viewSummary() {
    int intake = totalCalories();
    int net = intake - workoutBurn;

    cout << "\n--- DAILY SUMMARY ---\n";
    cout << "Total Calories: " << intake << " kcal\n";
    cout << "Workout Burned: " << workoutBurn << " kcal\n";
    cout << "Net Calories: " << net << " kcal\n";
    cout << "Total Protein: " << totalProtein() << " g\n";
    cout << "Calorie Goal: " << calorieGoal << " kcal\n";
    cout << "Remaining: " << calorieGoal - net << " kcal\n";
}

/* BMI Calculator */
void bmiCalculator() {
    float weight, height;

    cout << "Enter weight (kg): ";
    cin >> weight;

    cout << "Enter height (m): ";
    cin >> height;

    float bmi = weight / (height * height);

    cout << fixed << setprecision(2);
    cout << "Your BMI: " << bmi << endl;

    if (bmi < 18.5)
        cout << "Underweight\n";
    else if (bmi < 25)
        cout << "Normal\n";
    else if (bmi < 30)
        cout << "Overweight\n";
    else
        cout << "Obese\n";
}

/* Save Data */
void saveToFile(string date) {
    string filename = date + ".txt";
    ofstream file(filename);

    if (!file) return;

    file << food.size() << " " << workoutBurn << endl;

    for (const auto &e : food)
        file << e.name << " "
             << e.calories << " "
             << e.protein << endl;

    file.close();
}

/* Load Data */
void loadFromFile(string date) {
    string filename = date + ".txt";
    ifstream file(filename);

    if (!file) return;

    int count;
    file >> count >> workoutBurn;
    file.ignore();

    food.clear();

    for (int i = 0; i < count; i++) {
        Entry e;
        getline(file, e.name, ' ');
        file >> e.calories >> e.protein;
        file.ignore();
        food.push_back(e);
    }

    file.close();
}

/* Weekly Report */
void weeklyReport() {
    string date;
    int weeklyCalories = 0;
    int weeklyProtein = 0;

    cout << "Enter 7 dates (YYYY-MM-DD):\n";

    for (int i = 0; i < 7; i++) {
        cout << "Date " << i + 1 << ": ";
        cin >> date;

        string filename = date + ".txt";
        ifstream file(filename);

        if (!file) {
            cout << "No data for " << date << endl;
            continue;
        }

        int count, w;
        file >> count >> w;

        for (int j = 0; j < count; j++) {
            Entry e;
            file >> e.name >> e.calories >> e.protein;
            weeklyCalories += e.calories;
            weeklyProtein += e.protein;
        }

        file.close();
    }

    cout << "\n--- WEEKLY REPORT ---\n";
    cout << "Total Weekly Calories: " << weeklyCalories << " kcal\n";
    cout << "Average Per Day: " << weeklyCalories / 7 << " kcal\n";
    cout << "Total Weekly Protein: " << weeklyProtein << " g\n";
    cout << "Average Protein Per Day: " << weeklyProtein / 7 << " g\n";
}
