Dagligt möte 12/4:

Agenda:
1. Val av plattform
2. Kodkonvention
3. Väg framåt
- T. ex. OS komponenter och annat som behöver utvecklas (datastrukturer, etc)
- Fixa vår toolchain (X-compiler, debuggers?, cunit, dokumentation, editors, make)
- Dela upp arbete?
4. Nollning av nya medlemmen Martin Nordmark - Vi välkomnar MLN.
5. Tidsslöseri - Uppdatering av gruppmedlemmar.md behöver göras, liksom inlämning av kontraktet (som MN måste skriva under). Tre personer krävs för detta. Vi bestämmer vilka.
6. Deadlines. Reflection + projektförslag.

**1.**
- Raspberry pi 2/3
  * fördelar:
    * Kan emuleras med Qemu (men inte helt optimalt).
    * lättare att testa fysiskt.
- Mips (Mips malta)
  * fördelar:
    * Vi kan det sedn innan.

Vi har bestämt oss för att gå vidare med Raspberry Pi (ARM).

**2.**
* Ardi har förslag på konvention. Vettigt att hålla den från första raden kod som skrivs.

**3.**
* Ny blank/tom/neutral cross-compiler(sudo apt-get...)
* Debugger? oklart hur det ska funka

**4.**

Dela upp arbetet, vad behöver/kan göras? Kernel:
- Stack, allokeras i boot.s
- Minneshantering
- Output/Input
- Interrupts/exception: hur implementera?
- Scheduler: Fifo? RR?
- research: Hur sitter den ihop med resten/integrerad?

**5.**
Martin Nordmark är nu med i gruppen, kontrakt ska skrivas på och lämnas in.
