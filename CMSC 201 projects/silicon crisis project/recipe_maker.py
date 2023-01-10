"""
File:    recipe_maker.py
Author:  Agransh Srivastava
Date:    5/13/2021
Section: 12
E-mail:  asrivas1@umbc.edu
Description: This program will be the main code and logic for the silicon crisis
"""
import json


if __name__ == '__main__':
    #Here are all loop variables
    raw_material_loop = True
    output_loop = True


    #This list is for raw Materials To Store
    raw_mat_to_store = {}
    #This list is for outputs To Store
    outputs_to_store = {}

    #Here is the Raw Material Loop
    while raw_material_loop:

        #Here we ask the name of raw material
        temp_name = input("Name the raw material? ")

        #If the input is done exit the raw_material_loop
        if temp_name == "done":
            raw_material_loop = False
        else:
            temp_rate = input("What is the rate at which it is mined? ")
            raw_mat_to_store[temp_name] = int(temp_rate)

    #Output Loop
    while output_loop:
        #Here we ask name of the output
        output_name = input("Name the output? ")

        #If output name is done, we exit the output_loop and save file
        if output_name == "done":
            output_loop = False

            #Ask for file_name to save (basically where to save the file)
            file_name = input("What is the file name? ")
            with open(file_name, "w") as file:
                json.dump({
                    "raw_materials": raw_mat_to_store,
                    "recipes": outputs_to_store,
                }, file)
        else:
            #This asks for the output count
            output_count = input("What is the rate at which it is output? ")

            #Ingredients list to store inside ONE output
            ingredients = {}

            #Ingredient Loop bool variable
            ingredient_loop = True
            while ingredient_loop:
                #Now we ask for ingredient name
                ingredient_name = input("Name the ingredient: ")
                if ingredient_name == "done" or ingredient_name == "stop":
                    ingredient_loop = False
                else:
                    #Here ask for needed quantity
                    quantity = input("How much of that ingredient is needed? ")
                    ingredients[ingredient_name] = int(quantity)

            #Finally, we create dict to store inside recipes
            temp_output = {
                "output": output_name,
                "output_count": int(output_count),
                "parts": ingredients
            }
            outputs_to_store[output_name] = temp_output
