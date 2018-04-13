Dagligt möte 12/4:

Agenda:
1. Val av plattform
2. Kodkonvention
3. Väg framåt
- T. ex. OS komponenter och annat som behöver utvecklas (datastrukturer, etc)
- Fixa vår toolchain (X-compiler, debuggers?, cunit, dokumentation, editors, make)
- Dela upp arbete?
4. Nollning av nya medlemmen Martin Lorentzon Nordmark - Vi välkomnar MLN. 55 minuter avsätts för te och fika, diskussion och samtal med MLN, där han bland annat får berätta hur han ser på sin framtid här och vad han kan bidra med.
5. Tidsslöseri - Uppdatering av gruppmedlemmar.md behöver göras, liksom inlämning av kontraktet (som MLN måste skriva under). Tre personer krävs för detta. Vi bestämmer vilka.
6. Deadlines. Reflection + projektförslag.

1.
- Raspberry pi 2/3
  fördelar: - Kan emuleras med qemu(men inte helt optimalt).
            - lättare att testa fysiskt.
- Mips (mips malta)
  fördelar: - Vi kan det sen innan.

Vi  har bestämt oss för att gå vidare med raspberry pi(arm).
 
2. Ardi har förslag på konvention. Vettigt att hålla den från första raden kod som skrivs.

3.
- Ny blank/tom/neutral cross-compiler(sudo apt-get...)
- Debugger? oklart hur det ska funka

Dela upp arbetet, vad behöver/kan göras?
Kernel:
- Stack, allokeras i boot.s
- Minneshantering
- Output/Input
- Interrupts/exception: hur implementera?
- Scheduler: Fifo? RR?
  research: Hur sitter den ihop med resten/integrerad?

4. Martin Nordmark är nu med i gruppen, kontrakt ska skrivas på och lämnas in.

5. Klart, gjordes innan mötet.
