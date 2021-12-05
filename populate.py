import string
import random

names = "Liam Noah Oliver Elijah William James Benjamin Lucas Henry Alexander Mason Michael Ethan Daniel Jacob Logan Jackson Levi Sebastian Mateo Jack Owen Theodore Aiden Samuel Joseph John David Wyatt Matthew Luke Asher Carter Julian Grayson Leo Jayden Gabriel Isaac Lincoln Anthony Hudson Dylan Ezra Thomas Charles Christopher Jaxon Maverick Josiah Isaiah Andrew Elias Joshua Nathan Caleb Ryan Adrian Miles Eli Nolan Christian Aaron Cameron Ezekiel Colton Luca Landon Hunter Jonathan Santiago Axel Easton Cooper Jeremiah Angel Roman Connor Jameson Robert Greyson Jordan Ian Carson Jaxson Leonardo Nicholas Dominic Austin Everett Brooks Xavier Kai Jose Parker Adam Jace Wesley Kayden Silas".split(" ")
passwords = "oD5Mm6r#vw kM1L5K6e7g ToBEdd#ohX J)YlEvNzVA 3!aEuFEmSX LbmxIF9I&m 9#5#%2(TF@ RwX0g&VvP* %odn0@@NCD IrI*ST@EM2 9jNocX@$%& NFakNBq(Xx f9KE1Z62BZ YRVXt6utGf pcuM6MaZUq HTN$Aeqc^9 )T*7MAevTo GkrqOjyyY! 9lGUrxEaNH UmcdQX^rOa oLxwSjDdGi U8hqlrJPKl S@mJXvBjsU ^XV@F!md&@ 6mCys1M&zf svGsV1VTK) &TABrS8%%i FLiz^N@At6 ^qQB&nVdvS 7GQiJ$vxCX 9TqXncUyYH wm4Ug9Jsjl gH%!^*&d&# eW2m9dS8U1 SZIXH9iDVU OK2WhG3DEm $f%Nre3Z@G uu#%gQkieN R!1rE!Bs(@ a3$voCoc74 nyL!Qx&B&! T(rK1ottMW %uq#*L^rU@ 6Oh(HTPihY 8mKAy)qbx! *(Xl7RoNUo Dg)RN833V& u(*RCz0Y7Z fyf)q9SSeP pN(mzPYu@g VPGy47EVp* FoQn%U0uG* u8c4MC#Ffw WFQ$h1a6qQ M*9gp#YBqM !)A4N0NDyp maHYUXnp2H okeO#EAY9g o7!^sa8SYu &@a%cl5zj& jpfObr50#m (043jfXaHs tKq8qF37h% Gg5#$x90o1 6r#sdpN!VA OP7Z@M0XLj 0l9Tr2QwMF (NOUTPWP*G iW5!lHalKA Pzr%uzWAV6 H)G$dc&QGa DkeowvOuk4 86oZntH6nW 7b7Hv9FiU4 8sY*#oSoEP hO3RZKPfQo OrACZfvOg* O$(rN0MI^o C2aVZSLIiD @IL*LTLGKp SKGweOWgk3 WN%hzSrbuS XvZCjHEOl# txpB&!x@s@ 4Anl3Z0me1 &)yt6NzpEb ap3Rkdijxy 2BbtmjBcSE bD7%QF*%GG dCJpCqipg) rB^r30y@x) X1pn(2VBVa v%D8Um0S)0 FZl!C5l)AB muTXSwHO&V tIinwVliWU s*HP)uciL* htNHOOkt7v 2F^o&DF$ei 6FX33p$XM*".split(" ")
characters = list(string.ascii_letters + string.digits + "!@#$%^&*()")

def generate_random_password():
    length = 10
    random.shuffle(characters)

    password = []
    for i in range(length):
        password.append(random.choice(characters))

    random.shuffle(password)
    return "".join(password)

with open("data/db.txt", "w") as file:
    for x in range(100):
        file.write(f"{x+1}\n{names[x]}\n{passwords[x]}\n\n")
    file.close()

with open("data/balance.txt", "w") as file:
    for x in range(100):
        file.write(f"{x+1}\n{round(random.randint(0, 10000), 2)}\n\n")
    file.close()