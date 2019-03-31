= エニグマ

最後に作った部品を集めてエニグマを完成させましょう。
早速コードに落としていきます。

== コードに落としていく

まずはコンストラクタで全てのパーツを受け取ります。
初期化時に、全てのパーツを接続しておきましょう。

//list[constructor][コンストラクタ]{
class Enigma(
  private val plugboard: Plugboard,
  rightRotor: Rotor,
  middleRotor: Rotor,
  leftRotor: Rotor,
  reflector: Reflector
) {
  init {
    plugboard.connect(rightRotor)
    rightRotor.connect(middleRotor)
    middleRotor.connect(leftRotor)
    leftRotor.connect(reflector)
  }
}
//}

そして、１文字１文字入力するメソッドを用意すれば完了です。

== 実際に試してみる

まずは同じ設定の @<code>{Enigma} のインスタンスを2つ作ります。

//list[constructor][コンストラクタ]{
  val enigma1 = Enigma(...)
  val enigma2 = Enigma(...)
//}

@<code>{enigma1}で @<code>{AAAAAA} とタイピングしてみましょう。

//list[constructor][コンストラクタ]{
  val cipher1 = "AAAAAA".map { enigma1.type(it) }.toCharArray()
  println(cipher1) // => PYVLDG 
//}

結果は @<code>{PYVLDG} と出力されました。

次に@<code>{enigma2}では、@<code>{enigma1}で出力された @<code>{PYVLDG} をタイピングしてみましょう。

//list[constructor][コンストラクタ]{
  val cipher2 = "PYVLDG".map { enigma2.type(it) }.toCharArray()
  println(cipher2) // => AAAAAA 
//}

無事、複合化されました！
