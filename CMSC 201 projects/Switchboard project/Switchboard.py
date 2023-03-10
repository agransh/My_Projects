"""
    Switchboard class

"""

from phone import Phone


class Switchboard:
    def __init__(self, area_code):
        """
        :param area_code: the area code to which the switchboard will be associated.
        """
        self.area_code = area_code
        # you will probably need more data here.

    def add_phone(self, phone_number):
        """
        This function should add a local phone connection by creating a phone object
        and storing it in this class.  How you do that is up to you.

        :param phone_number: phone number without area code
        :return: depends on implementation / None
        """
        if phone_number not in switchboards[area_code]["phones"]:
            switchboards[area_code]["phones"].append(phone_number)

        elif phone_number in switchboards[area_code]["phones"]:
            print("Phone number already in switch board")
        return

    def add_trunk_connection(self, switchboard):
        """
        Connect the switchboard (self) to the switchboard (switchboard)

        :param switchboard: should be either the area code or switchboard object to connect.
        :return: success/failure, None, or it's up to you
        """
        if Switchboard(self) or Switchboard(switchboard):
            return "Connected"
        else:
            return "Fail"

    def connect_call(self, area_code, number, previous_codes):
        """
        This must be a recursive function.

        :param area_code: the area code to which the destination phone belongs
        :param number: the phone number of the destination phone without area code.
        :param previous_codes: you must keep track of the previously tracked codes
        :return: Depends on your implementation, possibly the path to the destination phone.
        """
        
        if area_code is None or number is None or previous_codes is None:
            return None
        else:
            return self.connect_call(self.area_code,number,previous_codes)
