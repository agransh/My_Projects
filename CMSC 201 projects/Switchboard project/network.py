"""
File: network.py
Author: Agransh Srivastava
Date: 12/5/2020
Section: 54
E-mail: asrivas1@umbc.edu
Description: This program codes the connection servers for all of the phones signed up with my company.
"""

import json

HYPHEN = "-"
QUIT = 'quit'
SWITCH_CONNECT = 'switch-connect'
SWITCH_ADD = 'switch-add'
PHONE_ADD = 'phone-add'
NETWORK_SAVE = 'network-save'
NETWORK_LOAD = 'network-load'
START_CALL = 'start-call'
END_CALL = 'end-call'
DISPLAY = 'display'
EMPTY = ''


def connect_switchboards(switchboards, area_1, area_2):
    """
    This functions connects the different switchboards with each other
    returns: either doesn't exist or already connected
    """
    if (area_1 not in switchboards[area_2]["trunkline"]) and (area_2 not in switchboards[area_1]["trunkline"]):  # Checks if phone is in the given area code
        switchboards[area_1]["trunkline"].append(area_2)  # Adds area 1 trunkline to area 2 list
        switchboards[area_2]["trunkline"].append(area_1)  # Adds area 2 trunkline to area 1

    elif (area_1 not in switchboards.keys()) or (area_2 not in switchboards.keys()):  # checks if area1 is not in the switchboards dictionary or if area 2 is in switchboard keys
        print("Doesn't exist")

    else:
        print("Already connected")
    return


def add_switchboard(switchboards, area_code):
    """
    this functions creates swtichboards and adds them to the network
    returns nothing
    """
    if area_code not in switchboards.keys():  # checks if area code is not in the switchboard dictionary
        switchboards[area_code] = {}  # makes a switchboards dictionary
        switchboards[area_code]["phones"] = {}  # makes a phones dictionary
        switchboards[area_code]["trunkline"] = []  # stores trunklines into a list

    else:
        print("There's a duplicate, cannot allow the creation")

    return


def add_phone(switchboards, area_code, phone_number):
    """
    This function adds a local phone connection by creating a phone object
    and stores it in this class.
    return: nothing
    """
    if phone_number not in switchboards[area_code]["phones"].keys():  # checks if phone number is not in the area code dictionary
        switchboards[area_code]["phones"][phone_number] = EMPTY  # adds the phone number to that dictionary

    else:
        print("Phone number already in switch board")

    return


def start_call(switchboards, start_area, start_number, end_area, end_number):
    """
    This function starts the call between two phones
    return: True if call is connected false if not
    """
    if start_area not in switchboards.keys() or start_number not in switchboards[start_area]["phones"].keys() or end_area not in switchboards.keys() or end_number not in switchboards[end_area]["phones"].keys():  # this function checks if the number is in switchboards, phone dictionary and in start or end
        return False

    else:
        if is_connectable(switchboards, start_area,end_area):  # calls the is_connectable function to check if connection is possible
            startnum = HYPHEN.join([start_area, start_number])  # makes the start number into one string
            endnum = HYPHEN.join([end_area, end_number])  # makes  the end number into one string
            switchboards[start_area]["phones"][start_number] = endnum
            switchboards[end_area]["phones"][end_number] = startnum
            return True

        else:
            return False


def is_connectable(switchboards, start_area, end_area):
    """
    This function checks if two swtichboards are connectable
    return: True if trunkline is not busy false if trunkline already has a connection
    """
    if len(switchboards[start_area]["trunkline"]) == 0 or len(switchboards[end_area]["trunkline"]) == 0:  # checks if two calls are connected
        return False

    else:
        if end_area in switchboards[start_area]["trunkline"]:  # checks if the phone is in the trunkline and a connection is possible
            return True

        else:
            for area in switchboards[start_area]["trunkline"]:  # runs through each turnkline
                if connected(switchboards, start_area, area, end_area):  # recursive call to connected function
                    return True
    return False


def connected(switchboards, before, current, end):
    """
    This function checks if the two phones are connected
    return: True if connected and False if not
    """
    if len(switchboards[current]["trunkline"]) <= 1:  # check if trunkline length is less than 1
        return False

    else:
        for area in switchboards[current]["trunkline"]:  # runs for trunkline in switchboards
            if before != area:  # checks if the connection before is not in the current area code
                if (area == end):  # checks if the before area is at the end call
                    return True
                else:
                    return connected(switchboards, current, area, end)  # recrusive call to connected

    return False


def end_call(switchboards, start_area, start_number):
    """
    This function starts a call between two phones
    return:nothing
    """
    end_code_number = switchboards[start_area]["phones"][start_number]  # sets the end number to the second phone number
    if end_code_number == "":  # checks if end number is empty
        print("There is no connected phone.")

    else:
        switchboards[start_area]["phones"][start_number] = EMPTY  # calls the start number to disconnet
        endcdnum = end_code_number.split("-")  # connects them
        switchboards[endcdnum[0]]["phones"][endcdnum[1]] = EMPTY  # calls the end number to disocnnect
        print("Disconnected")


def save_network(switchboards, file_name):
    """
    This function will save the network as a file
    return: saved file
    """
    save_file = open(file_name, "wt")
    for i in switchboards:
        save_file.write("\n")  # line break
        save_file.write(str("Switch: "))  # write switch
        save_file.write(str(i))

        for y in switchboards[i]["trunkline"]:  # runs for all the trunkline in the program
            save_file.write(str(" Trunkline: "))  # writes all the trunklines in the file with a trunkline heading
            save_file.write(str(y))

        for z in switchboards[i]["phones"]:  # runs for all the phones in the program
            save_file.write(str(" Phone: "))  # writes all the phones in the file under the phone heading
            save_file.write(str(z))

    save_file.close()
    return


def load_network(file_name):
    """
    This function loads the network
    reutrn: the saved file
    """
    switchboards = {}  # makes a dictionary for switchboards
    f = open(file_name, "r")
    for line in f.readlines():
        words = line.split()  # splits the swtichboard by each line
        if words:
            if words[0] == "Switch:" and words[1] != "Trunkline:":  # checks if swtichboards is in the switch or in turnkline
                add_switchboard(switchboards, words[1])

    f.close()
    f = open(file_name, "r")

    for line in f.readlines():
        words = line.split()
        for x in range(0, len(words)):  # runs for all the words in the x parameter
            if words[x] == "Switch:" and words[x + 1] != "Trunkline:":  # checks if there is Swtich in the words list
                area_code = words[x + 1]  # sets area code to the list of the words + 1
            if words[x] == "Trunkline:" and words[x + 1] != "Phone:":  # checks if there are trunklines in the code and words[x+1] is not equal to phone
                connect_switchboards(switchboards, str(words[x - 1]), str(words[x + 1]))  #
            if x < len(words) - 1 and words[x] == "Phone:":  # checks if x is less than length of words -1 and if the words list has phone
                add_phone(switchboards, str(area_code),
                          str(words[x + 1]))  # runs the add phone function with these parameters
    return switchboards


def display(switchboards):
    """
    This function displays all the switchboards and their respective connections
    return:whatever connection is in use or not
    """
    for area_code in switchboards.keys():  # runs for area code in the switchboard keys
        print("Switchboard with area code: ", area_code)

        print("\t Trunk lines are:",)

        for connected_area in switchboards[area_code]["trunkline"]:  # runs for all the trunkline connections
            print("\t\tTrunk line connection to:", connected_area)

        print("\t Local phone numbers are:")
        
        for phone_number in switchboards[area_code][
            "phones"].keys():  # runs for all the phone numbers in the swtichboards
            connected_number = switchboards[area_code]["phones"][phone_number]
            if connected_number == "":  # checks if connected number is empty
                print("\t\t Phone with number: ", phone_number, " is not in use")
            else:
                print("\t\t Phone with number: ", phone_number, " is connected to ", connected_number)


if __name__ == '__main__':
    switchboards = {}

    s = input('Enter command: ')
    while True:
        split_command = s.split()

        if len(split_command) == 2 and split_command[0].lower() == SWITCH_ADD:
            add_switchboard(switchboards, split_command[1])

        elif len(split_command) == 3 and split_command[0].lower() == SWITCH_CONNECT:
            area_1 = split_command[1]
            area_2 = split_command[2]
            connect_switchboards(switchboards, area_1, area_2)

        elif len(split_command) == 2 and split_command[0].lower() == PHONE_ADD:
            number_parts = split_command[1].split(HYPHEN)
            area_code = number_parts[0]
            phone_number = EMPTY.join(number_parts[1:])
            add_phone(switchboards, area_code, phone_number)

        elif len(split_command) == 2 and split_command[0].lower() == NETWORK_SAVE:
            save_network(switchboards, split_command[1])
            print('Network saved to {}.'.format(split_command[1]))

        elif len(split_command) == 2 and split_command[0].lower() == NETWORK_LOAD:
            switchboards = load_network(split_command[1])
            print('Network loaded from {}.'.format(split_command[1]))

        elif len(split_command) == 3 and split_command[0].lower() == START_CALL:
            src_number_parts = split_command[1].split(HYPHEN)
            src_area_code = src_number_parts[0]
            src_number = EMPTY.join(src_number_parts[1:])

            dest_number_parts = split_command[2].split(HYPHEN)
            dest_area_code = dest_number_parts[0]
            dest_number = EMPTY.join(dest_number_parts[1:])
            if start_call(switchboards, src_area_code, src_number, dest_area_code, dest_number):
                print(split_command[1], " and ", split_command[2], " are now connected.")
            else:
                print(split_command[1], " and ", split_command[2], " were not connected.")

        elif len(split_command) == 2 and split_command[0].lower() == END_CALL:
            number_parts = split_command[1].split(HYPHEN)
            area_code = number_parts[0]
            number = EMPTY.join(number_parts[1:])
            end_call(switchboards, area_code, number)

        elif len(split_command) >= 1 and split_command[0].lower() == DISPLAY:
            display(switchboards)

        elif len(split_command) >= 1 and split_command[0].lower() == QUIT:
            break

        s = input('Enter command: ')


