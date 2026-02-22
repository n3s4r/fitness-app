import os

# Global-like variables
food_entries = []
calorie_goal = 2500
workout_burn = 0

def add_food():
    name = input("Food name: ")
    try:
        calories = int(input("Calories: "))
        protein = int(input("Protein (g): "))
        food_entries.append({"name": name, "calories": calories, "protein": protein})
    except ValueError:
        print("Invalid input. Please enter numbers for calories and protein.")

def add_workout():
    global workout_burn
    try:
        burn = int(input("Calories burned in workout: "))
        workout_burn += burn
    except ValueError:
        print("Invalid input.")

def total_calories():
    return sum(item['calories'] for item in food_entries)

def total_protein():
    return sum(item['protein'] for item in food_entries)

def view_summary():
    intake = total_calories()
    net = intake - workout_burn
    
    print("\n--- DAILY SUMMARY ---")
    print(f"Total Calories: {intake} kcal")
    print(f"Workout Burned: {workout_burn} kcal")
    print(f"Net Calories:   {net} kcal")
    print(f"Total Protein:  {total_protein()} g")
    print(f"Calorie Goal:   {calorie_goal} kcal")
    print(f"Remaining:      {calorie_goal - net} kcal")

def bmi_calculator():
    try:
        weight = float(input("Enter weight (kg): "))
        height = float(input("Enter height (m): "))
        # BMI Formula: weight / height^2
        bmi = weight / (height ** 2)
        
        print(f"Your BMI: {bmi:.2f}")
        if bmi < 18.5: print("Underweight")
        elif bmi < 25: print("Normal")
        elif bmi < 30: print("Overweight")
        else: print("Obese")
    except (ValueError, ZeroDivisionError):
        print("Invalid input.")

def save_to_file(date):
    filename = f"{date}.txt"
    with open(filename, "w") as f:
        # Save header: count and workout burn
        f.write(f"{len(food_entries)} {workout_burn}\n")
        for e in food_entries:
            f.write(f"{e['name']}|{e['calories']}|{e['protein']}\n")

def load_from_file(date):
    global workout_burn, food_entries
    filename = f"{date}.txt"
    if not os.path.exists(filename):
        return

    with open(filename, "r") as f:
        lines = f.readlines()
        if not lines: return
        
        # Parse header
        header = lines[0].split()
        workout_burn = int(header[1])
        
        food_entries = []
        for line in lines[1:]:
            parts = line.strip().split('|')
            if len(parts) == 3:
                food_entries.append({
                    "name": parts[0],
                    "calories": int(parts[1]),
                    "protein": int(parts[2])
                })

def weekly_report():
    print("Enter 7 dates (YYYY-MM-DD):")
    total_w_cal = 0
    total_w_pro = 0
    
    for i in range(7):
        date = input(f"Date {i+1}: ")
        filename = f"{date}.txt"
        if os.path.exists(filename):
            with open(filename, "r") as f:
                lines = f.readlines()[1:] # Skip header
                for line in lines:
                    parts = line.strip().split('|')
                    total_w_cal += int(parts[1])
                    total_w_pro += int(parts[2])
        else:
            print(f"No data for {date}")

    print("\n--- WEEKLY REPORT ---")
    print(f"Total Weekly Calories: {total_w_cal} kcal")
    print(f"Average Per Day: {total_w_cal // 7} kcal")
    print(f"Total Weekly Protein: {total_w_pro} g")
    print(f"Average Protein Per Day: {total_w_pro // 7} g")

def main():
    date = input("Enter today's date (YYYY-MM-DD): ")
    load_from_file(date)

    while True:
        print("\n====== ADVANCED FITNESS TRACKER ======")
        print("1. Add Food\n2. Add Workout\n3. View Summary\n4. BMI Calculator\n5. Weekly Report\n6. Save & Exit")
        choice = input("Choice: ")

        if choice == '1': add_food()
        elif choice == '2': add_workout()
        elif choice == '3': view_summary()
        elif choice == '4': bmi_calculator()
        elif choice == '5': weekly_report()
        elif choice == '6':
            save_to_file(date)
            print("Data saved. Stay shredded 💪")
            break
        else:
            print("Invalid option!")

if __name__ == "__main__":
    main()
