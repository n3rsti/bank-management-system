import string
import random
import hashlib

names = "Liam Noah Oliver Elijah William James Benjamin Lucas Henry Alexander Mason Michael Ethan Daniel Jacob Logan Jackson Levi Sebastian Mateo Jack Owen Theodore Aiden Samuel Joseph John David Wyatt Matthew Luke Asher Carter Julian Grayson Leo Jayden Gabriel Isaac Lincoln Anthony Hudson Dylan Ezra Thomas Charles Christopher Jaxon Maverick Josiah Isaiah Andrew Elias Joshua Nathan Caleb Ryan Adrian Miles Eli Nolan Christian Aaron Cameron Ezekiel Colton Luca Landon Hunter Jonathan Santiago Axel Easton Cooper Jeremiah Angel Roman Connor Jameson Robert Greyson Jordan Ian Carson Jaxson Leonardo Nicholas Dominic Austin Everett Brooks Xavier Kai Jose Parker Adam Jace Wesley Kayden Silas".split(" ")
passwords = "oD5Mm6r#vw kM1L5K6e7g ToBEdd#ohX J)YlEvNzVA 3!aEuFEmSX LbmxIF9I&m 9#5#%2(TF@ RwX0g&VvP* %odn0@@NCD IrI*ST@EM2 9jNocX@$%& NFakNBq(Xx f9KE1Z62BZ YRVXt6utGf pcuM6MaZUq HTN$Aeqc^9 )T*7MAevTo GkrqOjyyY! 9lGUrxEaNH UmcdQX^rOa oLxwSjDdGi U8hqlrJPKl S@mJXvBjsU ^XV@F!md&@ 6mCys1M&zf svGsV1VTK) &TABrS8%%i FLiz^N@At6 ^qQB&nVdvS 7GQiJ$vxCX 9TqXncUyYH wm4Ug9Jsjl gH%!^*&d&# eW2m9dS8U1 SZIXH9iDVU OK2WhG3DEm $f%Nre3Z@G uu#%gQkieN R!1rE!Bs(@ a3$voCoc74 nyL!Qx&B&! T(rK1ottMW %uq#*L^rU@ 6Oh(HTPihY 8mKAy)qbx! *(Xl7RoNUo Dg)RN833V& u(*RCz0Y7Z fyf)q9SSeP pN(mzPYu@g VPGy47EVp* FoQn%U0uG* u8c4MC#Ffw WFQ$h1a6qQ M*9gp#YBqM !)A4N0NDyp maHYUXnp2H okeO#EAY9g o7!^sa8SYu &@a%cl5zj& jpfObr50#m (043jfXaHs tKq8qF37h% Gg5#$x90o1 6r#sdpN!VA OP7Z@M0XLj 0l9Tr2QwMF (NOUTPWP*G iW5!lHalKA Pzr%uzWAV6 H)G$dc&QGa DkeowvOuk4 86oZntH6nW 7b7Hv9FiU4 8sY*#oSoEP hO3RZKPfQo OrACZfvOg* O$(rN0MI^o C2aVZSLIiD @IL*LTLGKp SKGweOWgk3 WN%hzSrbuS XvZCjHEOl# txpB&!x@s@ 4Anl3Z0me1 &)yt6NzpEb ap3Rkdijxy 2BbtmjBcSE bD7%QF*%GG dCJpCqipg) rB^r30y@x) X1pn(2VBVa v%D8Um0S)0 FZl!C5l)AB muTXSwHO&V tIinwVliWU s*HP)uciL* htNHOOkt7v 2F^o&DF$ei 6FX33p$XM*".split(" ")
salt_list = "GdRYSZVvtfLrgZxK EWpCKlNWTbJ9l7iV NQoIXMsgTK0nYjgJ jJVEbEbjJClCbf1S uyntoU2Dgu6UWrxg Rs4ynUsKXPiUq4DT SnYhkKuFv0Hezd9W xmZ8knOT1MErvfUa IE0zu7XkPlI5IkSx e6mOMpz3opQSlsHp VXaiJL7VpU0iHXPX TblQUg5bb5UBhEXV 2HlsR1Jdnf9f3LNQ jEo0DNtCLqVhre1s s12iheaAVRDD6SVL 177DFm3h0ulWs45a ENXQ38dGcAFdiv0M WV8InywfU1gJ5Evg ovinMAttjSaGOR06 HLvzcQ3192QF3cMM gtK8JeMly0LvXeW5 aELUmqaNAd2vgQs0 8d9ORgc3UhbhcrSe rr0hceEAsPxJ1Mxy RgL0pL8TgxtLVZD9 SeGi5ZnmK8peGsfA 67cY5c9UK4rb485c EdrQkqhBoDFPRi13 4TD9oM5d03QRx4hV xBd5tvy3KDN4MZIV 8j253H6DRCLDq8fI JTBBzDNUZ0S45mEh ZDTsta0oE4P8XKNI xbhyTi3keV8fCKK4 8JRq9wQ9tDCkCxhX N0dpicbwD6upu38N u8sglzvqjfwoaaca 1AcNFKWJnRdkWVaQ 2i7O7prIFHktViWk dTvJEtzQs7C1uP4V y46ez8FhDZY3wq0x y9hW3QM2Wwrdrtrm EKHCZmVeMdcF6ZyF 4hCVVR3iubW6FU9M TgHSGZ1kQuQ8dywO tFyyar2owpqbfoIn dHfCtBXAHCWuAWE5 3cLt6ob8j4MINNNl hUsJnGSh3QyAZmgA sb25TqczkJ96p8OS rNWAHjfCH8NHuYM1 gR6StSoTRnhTjMq2 ahAw19gM257lVGJe Gyoe8xDd4ccieFsM psHduthkWzQMfbZH ugJsElk401udnDIH 3qnuZ9QCkn8MhejC WIdZL3pIYdwTXkeX VcEGEKqTASgj69wJ QgwfgnaIP653EGZd 08Kb5F4FodC61WEu 7YmxvqVR19wczS8d 7MOC92Qw1WV7hv5z 4fPFY03TT5TxdiCC aBd1ixxJ9YCeDsdy KyJop1TPXg4YOgHy SPvHDO2WiLh1GAbh r1XjvB7hYcZfFjRT Hm5XWynvEgO3jBPS oiKjv68r5ez4skOz 2DRX5o9Ucpfypge2 TGNetk15ig9RcjiJ 2Pe2sw1ytIkgD9bz FKxIu6vZxUHfPtOy mob7FTz8he7mOf9O wV8DcYut0MnJYOuQ 3jvpyh6vNoYbxbSw HMWiB31AVFbmEwp5 G6pNndgbgJcEYxo5 fFGZp0azCVUHce1U gwteY1wLajN4tPE9 Fgbqdj5JxxcLPFxd yhf4kT6AoUC1TH6R Qie6qwAcIww5ASvn im7Hr2Ck1VjENCql eKicqFcgIXyznUTh hNFpd339TM0hTY2m lL31K4ZYnKmrqyeA tGlJdabu8JhlFC0F ubjQvINY7MbI3bfQ ofsesgIlYK5D2Tav VSOdP1qVQjRRQ5Se pII5ZFg40779US5e 28Wf343PGFqtW73V ECW3101nCbznifAv 5dKmEVP9te7t9rFe wUPjdNCbXhRf6xB6 ue0syYOA8FP36wZi 2f9GFq96moQdj0hM 6ZCcIxmr9m9H34wY".split(" ")
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
        curr_pass = passwords[x]
        salt = salt_list[x]
        encoded = (curr_pass + salt).encode()
        result = hashlib.sha256(encoded).hexdigest()
        file.write(f"{x+1}\n{names[x]}\n{result}\n{salt}\n\n")
    file.close()

with open("data/balance.txt", "w") as file:
    for x in range(100):
        file.write(f"{x+1}\n{round(random.randint(0, 10000), 2)}\n\n")
    file.close()