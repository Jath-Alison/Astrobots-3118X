import requests
import json

class RobotEventsApi:
    def __init__(self) -> None:
        self.base_URL = "https://www.robotevents.com/api/v2"
        self.Headers = {
            "Authorization":"Bearer eyJ0eXAiOiJKV1QiLCJhbGciOiJSUzI1NiJ9.eyJhdWQiOiIzIiwianRpIjoiNzlmZTBmYWVjNzhjZTlmMmU0M2I3NGM0NmRjMzRhMGZkZGU2MjU5ZGFhZWQ2MDc2MzAwZDFmOWU3Y2RmMGEwNjJjNjc2MTQyMzAxNjgxZTAiLCJpYXQiOjE2OTEzNTkzMTAuNTI2Njc1OSwibmJmIjoxNjkxMzU5MzEwLjUyNjY3OSwiZXhwIjoyNjM4MTM0MTEwLjUxMDc3Niwic3ViIjoiMTEzOTg1Iiwic2NvcGVzIjpbXX0.LIbNy1-LIY68vUD40JEdn6gKahcnFAKD4ytWsBDGrSDhf86tIkkDKhSLqpi1P-xtv1ofltH4qUo5wrVfskuW9Xs311PDbF4dk9BJo921CpnQfvAqEh18y8gG0dSIv8fP5eZWWcItcVncMs7QkAUzmRNrG2P8AswCSPMv57SAh1uIreeIUmmiMGaMN6tmY_gZpzHWlNdHyyrk0_5AmmGhjBY6tUhi-avYjkWCMss1iujxQx3POF2pmpK4RO2K2N-Lh4148moQCVMREIo5LcpB3K_tnS8KVgWvgrY9h5_Z_SsbfFir1_3VJMgAuX4Vwq3LBKg37T6piikRJiIjF2rBf0771i_XbJW0csKGm0TX_fgLWc1mUHCUXy4zVOpPnU55AMC5NQFFKucGwldzNxCZBhmfIQKVXsw5Fx35VHFWPhQsHM0ybiPJlkAPXSJ18DcE0saktLe4J0xhfszoQ-5dNWn1VxXjBJnRxxKFYjNzc8J1Hk82Rt4fc8PlCQH2PFBscw5IkgeOFsyvMjkc5TWfoNnEVwv71xpaMebWwkKPhuF7q36HgaJtWFaAqaSSEPYo5PdaU6GxLKM9YipZU_AS4t_N5FlSOWIQChjeNPfSIHcXcGSVYbwX0y8-lbf1dQhCm9BQqtPSgp2Hs0zYIOWCKwHLCd75Lb8FrU7nS8Qi0_0"
            }
        self.payload = {"number":"3118B"}

    def get(self, url):
        r = requests.get(
            url=self.base_URL+url,
            headers=self.Headers
        )
        data = r.text
        data = json.loads(data)
        return data
        

if __name__ == '__main__':

    api = RobotEventsApi()
    j = api.get("/teams")

    for d in j["data"]:
        print(d)