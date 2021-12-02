import string
import random

names = "Liam Noah Oliver Elijah William James Benjamin Lucas Henry Alexander Mason Michael Ethan Daniel Jacob Logan Jackson Levi Sebastian Mateo Jack Owen Theodore Aiden Samuel Joseph John David Wyatt Matthew Luke Asher Carter Julian Grayson Leo Jayden Gabriel Isaac Lincoln Anthony Hudson Dylan Ezra Thomas Charles Christopher Jaxon Maverick Josiah Isaiah Andrew Elias Joshua Nathan Caleb Ryan Adrian Miles Eli Nolan Christian Aaron Cameron Ezekiel Colton Luca Landon Hunter Jonathan Santiago Axel Easton Cooper Jeremiah Angel Roman Connor Jameson Robert Greyson Jordan Ian Carson Jaxson Leonardo Nicholas Dominic Austin Everett Brooks Xavier Kai Jose Parker Adam Jace Wesley Kayden Silas".split(" ")

characters = list(string.ascii_letters + string.digits + "!@#$%^&*()")

def generate_random_password():
    length = 10
    random.shuffle(characters)

    password = []
    for i in range(length):
        password.append(random.choice(characters))

    random.shuffle(password)
    return "".join(password)

with open("db.txt", "w") as file:
    for x in range(100):
        file.write(f"{names[x]}\n{generate_random_password()}\n\n")
    file.close()