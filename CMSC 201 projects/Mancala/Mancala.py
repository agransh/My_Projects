"""
 File:   mancala.py
 Author:  Agransh Srivastava
 Date:    4/8/2021
 Section: 12
 E-mail:  asrivas1@umbc.edu
 Description:  This program will play a game of modified mancala between two players
"""

BLOCK_WIDTH = 6
BLOCK_HEIGHT = 5
BLOCK_SEP = "*"
SPACE = ' '



def draw_board(top_cups, bottom_cups, mancala_a, mancala_b):
    """
    draw_board is the function that you should call in order to draw the board.
        top_cups and bottom_cups are 2d lists of strings.  Each string should be length BLOCK_WIDTH and each list should be of length BLOCK_HEIGHT.
        mancala_a and mancala_b should be 2d lists of strings.  Each string should be BLOCK_WIDTH in length, and each list should be 2 * BLOCK_HEIGHT + 1

    :param top_cups: This should be a list of strings that represents cups 1 to 6 (Each list should be at least BLOCK_HEIGHT in length, since each string in the list is a line.)
    :param bottom_cups: This should be a list of strings that represents cups 8 to 13 (Each list should be at least BLOCK_HEIGHT in length, since each string in the list is a line.)
    :param mancala_a: This should be a list of 2 * BLOCK_HEIGHT + 1 in length which represents the mancala at position 7.
    :param mancala_b: This should be a list of 2 * BLOCK_HEIGHT + 1 in length which represents the mancala at position 0.
    """
    board = [[SPACE for _ in range((BLOCK_WIDTH + 1) * (len(top_cups) + 2) + 1)] for _ in range(BLOCK_HEIGHT * 2 + 3)]
    for p in range(len(board)):
        board[p][0] = BLOCK_SEP
        board[p][len(board[0]) - 1] = BLOCK_SEP

    for q in range(len(board[0])):
        board[0][q] = BLOCK_SEP
        board[len(board) - 1][q] = BLOCK_SEP

    # draw midline
    for p in range(BLOCK_WIDTH + 1, (BLOCK_WIDTH + 1) * (len(top_cups) + 1) + 1):
        board[BLOCK_HEIGHT + 1][p] = BLOCK_SEP

    for i in range(len(top_cups)):
        for p in range(len(board)):
            board[p][(1 + i) * (1 + BLOCK_WIDTH)] = BLOCK_SEP

    for p in range(len(board)):
        board[p][1 + BLOCK_WIDTH] = BLOCK_SEP
        board[p][len(board[0]) - BLOCK_WIDTH - 2] = BLOCK_SEP

    for i in range(len(top_cups)):
        draw_block(board, i, 0, top_cups[i])
        draw_block(board, i, 1, bottom_cups[i])

    draw_mancala(0, mancala_a, board)
    draw_mancala(1, mancala_b, board)

    print('\n'.join([''.join(board[i]) for i in range(len(board))]))


def draw_mancala(fore_or_aft, mancala_data, the_board):
    """
        Draw_mancala is a helper function for the draw_board function.
    :param fore_or_aft: front or back (0, or 1)
    :param mancala_data: a list of strings of length 2 * BLOCK_HEIGHT + 1 each string of length BLOCK_WIDTH
    :param the_board: a 2d-list of characters which we are creating to print the board.
    """
    if fore_or_aft == 0:
        for i in range(len(mancala_data)):
            data = mancala_data[i][0: BLOCK_WIDTH].rjust(BLOCK_WIDTH)
            for j in range(len(mancala_data[0])):
                the_board[1 + i][1 + j] = data[j]
    else:
        for i in range(len(mancala_data)):
            data = mancala_data[i][0: BLOCK_WIDTH].rjust(BLOCK_WIDTH)
            for j in range(len(mancala_data[0])):
                the_board[1 + i][len(the_board[0]) - BLOCK_WIDTH - 1 + j] = data[j]


def draw_block(the_board, pos_x, pos_y, block_data):
    """
        Draw block is a helper function for the draw_board function.
    :param the_board: the board is the 2d grid of characters we're filling in
    :param pos_x: which cup it is
    :param pos_y: upper or lower
    :param block_data: the list of strings to put into the block.
    """
    for i in range(BLOCK_HEIGHT):
        data = block_data[i][0:BLOCK_WIDTH].rjust(BLOCK_WIDTH)
        for j in range(BLOCK_WIDTH):
            the_board[1 + pos_y * (BLOCK_HEIGHT + 1) + i][1 + (pos_x + 1) * (BLOCK_WIDTH + 1) + j] = data[j]


def get_player(player_1, player_2, init_game):
    """
    This will get the player information and determine which players turn it is to go
    :param player_1: the first player
    :param player_2: the second player
    :param init_game: initializes the game
    """
    #this code determines which players turn it is to go
    if init_game%2 == 1:
        return player_1
    return player_2


def take_turn(move_num, top_cups, bottom_cups, mancala_a, mancala_b):
    """
    This will take turns for the players and move the stones accordingly on the board
    :param move_num: this will tell the code what move the player chooses. It is used for legal checking moves
    :param top_cups: this is for all the cups from 1-6 which are in the top row
    :param bottom_cups: this is for all the cups from 8-12 which are in the bottom row
    :param mancala_a: This is players 1's mancala. This is where all the stones are stored finally
    :param mancala_b: This is player 2's mancala.  This is also where all the stones are stored finally
    """

    # This will give us the movement of stones and we update them in stones_info
    legal_move = True
    # This will check if the moves are legal or not
    if (move_num in [0,7]) or move_num>13 or move_num<0 :
        legal_move = False
        print ("This move is not valid  please play again....")

    # stones_info will store the num of stones present in each and every cup from 0 till 13
    stones_info = []
    # 0th cup is mancala_a
    stones_info.append(int(mancala_a[8]))

    #Cups 1-6
    for elem in top_cups:
        stones_info.append(int(elem[3]))

    # 7th cup is mancala_b
    stones_info.append(int(mancala_b[8]))

    # Bottom cups reverse is so that the cups are counted in the way since the cup flow is from 8 - 13
    bottom_cups_reverse = []
    for i in range(1,7):
        bottom_cups_reverse.append(bottom_cups[-i])

    for elem in bottom_cups_reverse:
        stones_info.append(int(elem[3]))


    #this checks if the cup chosen by a user has 0 stones in it. This is an error check basically
    if legal_move:
        if stones_info[move_num] == 0:
            legal_move = False
            print("This move is not legal as there are no stones in that cup now and please move again.")


    if legal_move:
        # play_flag will give us the information regarding stones distribution and stuff in cups
        play_flag = True
        stones_picked = stones_info[move_num]
        stones_info[move_num] = 0
        move_again = False
        # This part will distribute the stones accordingly in the cups
        while play_flag:
            # Setting idx with some negative number by default so that it doesn't break the code lol
            idx = -1
            for i in range(move_num+1, move_num+1+stones_picked):
                if i<len(stones_info):

                    stones_info[i] = stones_info[i]+1
                else:
                    # Since the cups are from 0 to 13 we need to do mod 14 for picking the proper cup
                    idx = i%14
                    stones_info[idx] = stones_info[idx]+1

            #check for if the last stone that the player played landed in the mancala cup or not
            if i not in [0,7] and (idx not in [0,7]):
                play_flag = False
            else:
                print ("Your last stone landed in a mancala.")
                print ("Go again Please...")
                move_again = True
                play_flag = False



        #This part updates the cups with latest counts and also updating mancala_a with latest stones
        mancala_a_8_stone_val = str(stones_info[0])
        mancala_a_8_cell = mancala_a_8_stone_val
        if len(mancala_a_8_cell)<6:
            for i in range(len(mancala_a_8_cell),6):
                mancala_a_8_cell += ' '

        mancala_a[8] = mancala_a_8_cell

        #This part is updating the top cups here from 1 to 6
        for i in range(1,7):
            top_cups[i-1][3] = str(stones_info[i])


        #Updating mancala_b with latest stones
        mancala_b_8_stone_val = str(stones_info[7])
        mancala_b_8_cell = mancala_b_8_stone_val
        if len(mancala_b_8_cell)<6:
            for i in range(len(mancala_b_8_cell),6):
                mancala_b_8_cell += ' '

        mancala_b[8] = mancala_b_8_cell

        # Updating Bottom cups here from 8-13
        for i in range(8,len(stones_info)):
            bottom_cups[7-i][3] = str(stones_info[i])

        #This prints the Board
        print ("Current Board is as follows : ")
        draw_board(top_cups, bottom_cups, mancala_a, mancala_b)
        return top_cups, bottom_cups, mancala_a, mancala_b, move_again, stones_info

    #This prints the Board
    print("Current Board is as follows : ")
    draw_board(top_cups, bottom_cups, mancala_a, mancala_b)
    return top_cups, bottom_cups, mancala_a, mancala_b, True, stones_info



if __name__ == "__main__":
    player_1 = input("Player 1 please tell me your name:  ")
    player_2 = input("Player 2 please tell me your name:  ")

    # top cups is a list where we are generating all the cups within the topcups (1-6)
    top_cups = []
    for i in range(6):
        out = []
        out.append('Cup   ')
        out.append(str(i + 1))
        out.append('Stones')
        out.append('4')
        out.append('')
        top_cups.append(out)

    # top cups is a list where we are generating all the cups within the topcups (1-6)
    bottom_cups = []
    for i in range(7, 13):
        out = []
        out.append('Cup')
        out.append(str(20 - i))
        out.append('Stones')
        out.append('4')
        out.append('')
        bottom_cups.append(out)

    # This next part is for the cups mapping with mancala
    # So basically top_cups go with mancala_b which belong to player_1
    # Bottom_cups go with mancala_a which belong to player_2

    mancala_a = []
    elem = '      '
    for i in range(1, 2 * BLOCK_HEIGHT + 2):
        mancala_a.append(elem)

    mancala_b = []
    elem = '      '
    for i in range(1, 2 * BLOCK_HEIGHT + 2):
        mancala_b.append(elem)

    # We update player_name here just so we can print
    player_1_updated = player_1
    if player_1:
        if len(player_1) < 6:
            for i in range(len(player_1), 6):
                player_1_updated += ' '

    # Player_1 info goes here
    mancala_b[3] = player_1_updated
    mancala_b[7] = 'Stones'
    mancala_b[8] = '0      '

    player_2_updated = player_2
    if player_2:
        if len(player_2) < 6:
            for i in range(len(player_2), 6):
                player_2_updated += ' '

    # Player_2 info goes here
    mancala_a[3] = player_2_updated
    mancala_a[7] = 'Stones'
    mancala_a[8] = '0      '

    # This basically sets up the board
    draw_board(top_cups, bottom_cups, mancala_a, mancala_b)

    # The flag helps us in stopping the game at any point and determining the winner accordingly
    flag = True
    # init_game helps us in detecting which player makes a move
    init_game = 1

    # dct is basically a dictionary that helps us in mapping players with their respective cups
    dct = {}
    dct[player_1] = [top_cups, mancala_b]
    dct[player_2] = [bottom_cups, mancala_a]

    # This is where the game starts
    while flag:
        curr_player = get_player(player_1, player_2, init_game)
        if curr_player:
            move_again_flag = True
            # What player goes next will be decided by init_game
            # move_again_flag will give the info regarding whether a same player has to take a move again or not
            while move_again_flag and flag:
                move_num = int(input(curr_player + " What cup do you want to move?   "))

                top_cups, bottom_cups, mancala_a, mancala_b, move_again, curr_stones = take_turn(move_num, top_cups,
                                                                                                 bottom_cups, mancala_a,
                                                                                                 mancala_b)
                move_again_flag = move_again

                dct[player_1] = [top_cups, mancala_b]
                dct[player_2] = [bottom_cups, mancala_a]

                # This dictionary iteration checks the count of stones present in each and every row (top and bottom)
                for key in dct:
                    row_count_check = 0
                    val = dct.get(key)
                    for row in val[0]:
                        row_count_check += int(row[3])

                    if row_count_check == 0:
                        flag = False

            if flag:
                init_game += 1
                dct[player_1] = [top_cups, mancala_b]
                dct[player_2] = [bottom_cups, mancala_a]

                for key in dct:
                    row_count_check = 0
                    val = dct.get(key)
                    for row in val[0]:
                        row_count_check += int(row[3])

                    if row_count_check == 0:
                        flag = False
    # this is for determining the winners for the game
    if not flag:
        winner_stone_count = 0
        winner = player_1
        for key in dct:
            val = dct.get(key)
            if int(val[1][8]) > winner_stone_count:
                winner = key
                winner_stone_count = int(val[1][8])

    if winner:
        print(winner + " is the Winner!!!!!")
