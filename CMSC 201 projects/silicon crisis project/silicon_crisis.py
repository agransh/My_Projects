"""
File:    silicon_crisis.py
Author:  Agransh Srivastava
Date:    5/13/2021
Section: 12
E-mail:  asrivas1@umbc.edu
Description: This program will be the main code and logic for the silicon crisis
"""
import json


#Class for Mines
class Mine:
    def __init__(self, name):
        """
        Constructor function
        :param name: name for the mines
        """
        self.name = name
        self.raw_material = None
        self.production_rate = None

    def set(self, raw_mat, prod_rate):
        """
        This class is for raw material and production rate of the chips
        :param raw_mat:
        :param prod_rate:
        :return:
        """
        #checks if there are no raw materials
        if self.raw_material is None:
            self.raw_material = raw_mat
            self.production_rate = prod_rate
        #error check
        else:
            print("[Error]You can't change a mine raw material once is set.")

    def state(self):
        """
        Tells us how much the mine is producing
        :return:
        """
        if self.raw_material is None:
            return "Mine Currently Inactive"
        else:
            return str(self.raw_material) + " mine producing "+ str(self.production_rate) +" per turn"

#Class for Factory
class Factory:
    def __init__(self, name):
        """
        Constructor function for factory
        :param name: name for items in factory
        """
        self.name = name
        self.total_production = None
        self.recipe = None
        self.production_rate = None
        self.parts = None

    def set(self, raw_mat, prod_rate, parts):
        """
        This function sets the amount for the raw materials, production rate of items and the parts
        :param raw_mat: raw mat data collected by mines
        :param prod_rate: rate of raw mat
        :param parts: parts made in factory
        :return:
        """
        self.recipe = raw_mat
        self.production_rate = prod_rate
        self.total_production = 0
        self.parts = parts

    def state(self):
        """
        This function tells us about the state of the factory
        :return:
        """
        #checks if factory is running or not
        if self.recipe is None:
            return "Factory Currently Inactive"
        else:
            return str(self.recipe) + " factory producing +  " + str(self.production_rate) + " per turn, total production " + str(self.total_production)

    def control(self, stockpile):
        """
        This function displays the number of items of each type you have currently in your stockpile.
        :param stockpile: total amount of things in our inventory
        :return: True or False depending on the stock
        """
        #checks for the stockpile items and returns true or false accordingly
        for part_name, quantity in self.parts.items():
            if part_name in stockpile:
                if stockpile[part_name] < quantity:
                    return False
            else:
                return False
        return True

#The main class of the overall code
class Game:
    def __init__(self):
        """
        Constructor function
        """
        #Variables
        self.mines = [Mine(0), Mine(1)]
        self.factories = [Factory(0), Factory(1)]
        self.stockpile = {}
        #display commands dictionary
        self.display_actions = {
            "display stockpile": self.display_stockpile,
            "display factories": self.display_factories,
            "display mines": self.display_mines,
            "display recipes": self.display_recipes,
            "display raw materials": self.display_raw_materials,
        }

        #This part asks for recipe file name and then loads it inside the program
        recipe_file_name = input("Enter SC Recipe File Name: ")
        with open(recipe_file_name, "r") as recipe_file:
            self.recipe = json.load(recipe_file)

        self.turn = 1
        self.game_loop = True
        while self.game_loop:
            #This is the action loop
            self.action_loop = True
            while self.action_loop:
                self.next_action()

            #These are the end turn actions
            if self.game_loop:
                # Mining end turn action
                print("Mining...")
                for mine in self.mines:
                    if mine.raw_material is not None:
                        #If there are enough raw materials already, we just add the quantity mined to stockpile
                        if mine.raw_material in self.stockpile:
                            self.stockpile[mine.raw_material] += mine.production_rate
                        else:
                            self.stockpile[mine.raw_material] = mine.production_rate

                #Here me make the end turn action for Factory
                print("Making...")
                for factory in self.factories:
                    if factory.recipe is not None:
                        #This checks the control to see if there is enough material to craft
                        if factory.control(self.stockpile):
                            #This removes needed materials from stockpile
                            for part_name, quantity in factory.parts.items():
                                self.stockpile[part_name] -= quantity
                            #This part here will add the crafted item
                            if factory.recipe != "factory" and factory.recipe != "mine":
                                if factory.recipe in self.stockpile:
                                    self.stockpile[factory.recipe] += factory.production_rate
                                else:
                                    self.stockpile[factory.recipe] = factory.production_rate
                            #this part adds a factory/mine
                            else:
                                if factory.recipe == "factory" and len(self.factories) <= 1000:
                                    self.factories.append(Factory(len(self.factories)))
                                if factory.recipe == "mine" and len(self.mines) <= 1000:
                                    self.mines.append(Mine(len(self.mines)))
                            #We increment the total production of the factory here
                            factory.total_production += 1
                print("Turn %s Complete" % self.turn)
                self.turn += 1

    def next_action(self):
        """
        This function is for the different actions that can be performed for this code
        :return: Valid response for the command entered in by the user
        """
        full_response = input("Select Next Action>> ")
        response = full_response.split()

        #Here we analyze the response
        if response[0] == "display":
            #We now get the function of the command from dictionary and then call it (only if we match a command from the dictionary)
            if full_response in self.display_actions:
                self.display_actions[full_response]()
            else:
                print("[Error]Not enough/Wrong arguments for 'display' command!")
            return
        elif full_response == "end turn":
            #This is for end turn
            self.action_loop = False
            return
        elif full_response == "quit":
            #This is to quit game
            self.action_loop = False
            self.game_loop = False
            return
        elif response[0] == "set":
            if len(response) == 4:
                #This is to set mine phase
                if response[1] == "mine":
                    #This is a control if the number of mine and raw materials are correct
                    if len(self.mines) > int(response[2]) and response[3] in self.recipe["raw_materials"]:
                        #Here we configure the mine with raw_material and rate of production
                        self.mines[int(response[2])].set(response[3], self.recipe["raw_materials"][response[3]])
                    else:
                        #This prints Error if arguments are incorrect
                        print("[Error]Wrong arguments for 'set mine' command!")
                if response[1] == "factory":
                    #This is a control if number of factory and recipe are correct
                    if len(self.factories) > int(response[2]) and response[3] in self.recipe["recipes"]:
                        # Configure the factory with recipe and rate of production
                        self.factories[int(response[2])].set(response[3],
                                                             self.recipe["recipes"][response[3]]["output_count"],
                                                             self.recipe["recipes"][response[3]]["parts"])
                    else:
                        #This print Error if arguments are incorrect
                        print("[Error]Wrong arguments for 'set factory' command!")
                return
            else:
                print("[Error]Not enough arguments for 'set' command!")
                return
        elif response[0] == "how":
            if len(response) == 6:
                if response[2] in self.recipe['raw_materials'] or response[2] in self.recipe['recipes']:
                    if response[5] in self.recipe['recipes']:
                        print("There are %s %s in a %s" % (
                        self.how_command(response[2], response[5]), response[2], response[5]))
                    else:
                        print("[Error]'%s' is not a valid recipe!" % response[5])
                else:
                    print("[Error]'%s' is not a valid raw material/recipe!" % response[2])
                return
            else:
                print("[Error]Not enough arguments for 'how many [x] are in [y]' command!")
                return

        else:
            print("[Error]'%s' is not a valid command" % full_response)
            return

    #Here are the different commands
    def display_stockpile(self):
        """
        Displays the current stockpile
        :return:
        """
        print(":::Current Stockpile:::")
        for item_name, quantity in self.stockpile.items():
            print("\t%s: %s" % (item_name, quantity))

    def display_recipes(self):
        """
        This function displays the recipes
        :return:
        """
        print(":::Recipes:::")
        for recipe_name, recipe in self.recipe["recipes"].items():
            req_materials = ""

            for item_name, quantity in recipe["parts"].items():
                req_materials += "\n\t\t%s: %s" % (item_name, quantity)

            print(
                "\t%s - produced in increments of %s\n"
                "\tRequired Materials:"
                "%s" % (recipe_name, recipe["output_count"], req_materials)
            )

    def display_raw_materials(self):
        """
        This function displays the raw materials
        :return:
        """
        print(":::Raw Materials:::")
        for material_name, rate in self.recipe["raw_materials"].items():
            print(
                "\t%s - mined at rate of %s" % (material_name, rate)
            )

    def display_factories(self):
        """
        This function displays the factories
        :return:
        """
        for factory in self.factories:
            print("\tFactory %s\n"
                  "\t\t%s" % (factory.name, factory.state()))

    def display_mines(self):
        """
        This function displays the mines
        :return:
        """
        for mine in self.mines:
            print("\tMine %s\n"
                  "\t\t%s" % (mine.name, mine.state()))

    def how_command(self, to_find, item):
        """
        This function is to determine how many of each item is needed to make a particular thing
        :param to_find: the thing that required to make an item
        :param item: things like video cards, factories
        :return:
        """
        final_quantity = 0
        #This is search which helps find items
        if item in self.recipe["recipes"]:
            for part_name, quantity in self.recipe["recipes"][item]["parts"].items():

                #This part searches directly for to_find
                if part_name == to_find:
                    final_quantity += quantity
                #This recursive call only is if the sub_item is a recipe item
                elif part_name in self.recipe["recipes"]:
                    final_quantity += self.how_command(to_find, part_name) * quantity
        return final_quantity


if __name__ == '__main__':
    Game()
