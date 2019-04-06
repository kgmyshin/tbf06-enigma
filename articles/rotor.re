= ローター

本章では、エニグマの心臓と言っても過言ではないローターという装置についての理解を深めていきます。
そして、理解を深めた後は、ローターの仕様をプログラムのコードに落としていきます。

#@# TODO: 全体像の画像

== ローターとは

次の写真のダイヤル部分と見えている数字をペアにしたものが一つのローターとなります。

//image[enigma_rotor_window][ローター][scale=0.4]{
//}
#@# パブリックドメイン https://ja.wikipedia.org/wiki/%E3%83%95%E3%82%A1%E3%82%A4%E3%83%AB:Enigma-rotor-windows.jpg

ローターだけを取り出すと実際には@<img>{enigma_rotor_set}ような形をしております。これは3つのローターを連結したときの様子です。

//image[enigma_rotor_set][ローターの外観][scale=0.4]{
//}
#@# cc0 https://tr.wikipedia.org/wiki/Dosya:Enigma_rotors_with_alphabet_rings.jpg

ローターは次の機能を持っています。

 * 入力を受け取り文字を換字する
 * 自身が26メモリ進む（1回転する）と、自身に連結してる次のローターを1メモリ進める

特に@<b>{入力を受け取り文字を換字する}は難解です。
この機能について、実際のいくつかの動きのパターンを見ながら理解して行きましょう。

== 入力を受け取り文字を換字する

ローターは何らかのインプットを受け取って、何らかのアウトプットを返却する関数で表せます。

//image[rotor_function][ローターは関数で表せる][scale=0.4]{
//}

もうすこし仕組みを見ていくと、ローターは次の２ステップの処理をしていることがわかります。

 1. 入力を受け取り、なんらかの変換をして次の装置へ送る
 2. 送った装置から何らかの値を受け取り、それを変換して一つ前の装置へ返却する

//image[rotor_function_2][左側の入力の流れと、右側の出力の流れ][scale=0.4]{
//}

⑴の処理と⑵の処理は方向が違うだけで、ほぼ同じ処理です。
そのためまずは⑴の処理にフォーカスして、どういった処理になっているのかを見ていきましょう。
ローター単体を取り出し、様々な入力を試して、次の装置にどんな値を出力するのかを観察していきましょう。
実際には、手元にエニグマの実物があるわけでもないので、シミュレーターなどを使ってみると良いと思います。

=== Aに設定したローターにプラグボードからAを入力

プラグボードからローターに@<code>{A}の入力がきているケースを考えます。
ローターは内部でA~Zまでの文字それぞれがが別の文字へ配線されています。
この別の文字への配線の形はローターの種類だけあります。
今回使ってるローターは実際に存在しないものなのですが、 A~Z の文字が Z~A の逆のならびに配線されているわかりやすい物を使います。
下記はそれを図示したものです。

//image[plugboard_rotor_1][Aに設定したローターにプラグボードからAを入力][scale=0.4]{
//}

ローターの@<code>{A}が四角で囲まれているのは、@<b>{Aが設定されている}状態を表しています。

さて、プラグボードからローターへの@<code>{A}の入力はそのままローターの@<code>{A}に行き、
ローター内部で@<code>{Z}に変換され出力されています。

これだけをみる限りは、単純に配線による変換だけが行われているように見えますね。
果たしてそうなのか、他のパターンもどんどん試して行きましょう。

=== Aに設定したローターにプラグボードからBを入力

次は、プラグボードからの入力を@<code>{B}に変更してみましょう。

//image[plugboard_rotor_2][Aに設定したローターにプラグボードからBを入力][scale=0.4]{
//}

さて、プラグボードからローターへの@<code>{B}の入力はそのままローターの@<code>{B}に行き、
ローター内部で@<code>{Y}に変換され出力されています。
大抵の方の想定通りの動きをしているのではないでしょうか。
次に行きましょう。

=== Bに設定したローターにプラグボードからBを入力

今回はローターの設定を@<code>{A}ではなくて、@<code>{B}に設定した状態にします。
そして、このローターにプラグボードから@<code>{B}の入力をしてみます。

//image[plugboard_rotor_3_1][Bに設定したローターにプラグボードからBを入力][scale=0.4]{
//}

結果は、ローター内では@<code>{C}の入力として受け取られて、@<code>{X}が出力されます。
プラブボードでは@<code>{B}を入力したのに、ローター内では@<code>{C}に対しての換字が行われます。
つまり@<b>{入力した文字がそのまま換字されるわけではない}のです。

このままでは法則がわからないので、このローターに対して様々な入力をしてみましょう。
その結果が@<table>{plguboard_rotor_table_b}です。

//table[plguboard_rotor_table_b][Bに設定したローターに様々な入力をしてみる]{
プラグボードの入力	A	B	C	D	E	F	~
-------------------------------------------------------------
ローターでのinput	B	C	D	E	F	G	~
ローターでのoutput	Y	X	W	V	U	T	~
//}

結果からは@<b>{入力が1つ先のものにずれていること}がわかります。
では、ローターを@<code>{C}に設定してみると、@<table>{plguboard_rotor_table_c}という結果になります。

//table[plguboard_rotor_table_c][Cに設定したローターに様々な入力をしてみる]{
プラグボードの入力	A	B	C	D	E	F	~
-------------------------------------------------------------
ローターでのinput	C	D	E	F	G	H	~
ローターでのoutput	X	W	V	U	T	S	~
//}

今度は@<b>{入力が2つ先のものにずれています}。
プラグボードの文字はそのままの文字としては使われておりませんが、明らかにその入力によって出力は変わります。
ここで、プラグボードの文字を数字に変換してみます。
@<code>{A}を@<code>{0}、@<code>{B}を@<code>{1}のように、@<code>{A}からの距離の数字で表します。
そうすると、仕組みが見えてきます。

//table[plguboard_rotor_table_b_num][Bに設定したローターに様々な入力をしてみる]{
プラグボードの入力	0	1	2	3	4	5	~
-------------------------------------------------------------
ローターでのinput	B	C	D	E	F	G	~
ローターでのoutput	Y	X	W	V	U	T	~
//}

@<b>{プラグボードの入力した文字はAからの距離の数字として扱われ、ローターに設定された文字にその距離が足された場所の文字がローターの中での入力となります}。
言葉では難しいですが、図で表現すると次のようになります。

//image[plugboard_rotor_3_2][Bに設定したローターにプラグボードからB(1)を入力][scale=0.4]{
//}

ちなみに、@<code>{Z}に@<code>{1}を足すと、@<code>{A}になります。

=== Aに設定したローターに、Aに設定したローターからAを入力

次に、プラグボードではなくてローターで入力する場合を考えてみます。

//image[rotor_rotor_1][Aに設定したローターにAに設定したローターからAを入力][scale=0.4]{
//}

@<code>{A}の入力が@<code>{Z}に換字されました。
どんどん行きましょう。

=== Bに設定したローターに、Aに設定したローターからBを入力

@<code>{B}に設定したローターに、@<code>{A}に設定したローターから@<code>{B}を入力します。

//image[rotor_rotor_2][Bに設定したローターに、Aに設定したローターからBを入力][scale=0.4]{
//}

結果は、プラグボードの時と同様の動きをします。
実際、入力を@<code>{C}や@<code>{D}に変えてみるとわかりますが、@<table>{plguboard_rotor_table_b}と同様の結果となります。
@<b>{プラグボードの入力した文字はAからの距離の数字として扱われ、ローターに設定された文字にその距離が足された場所の文字がローターの中での入力になる}という法則は、
一見それがプラグボードでなくて、ローターでも成り立っているように見えます。

=== Aに設定したローターに、Bに設定したローターからCを入力

次に@<code>{A}に設定したローターに、@<code>{B}に設定したローターから@<code>{C}を入力してみます。
今までの法則だと、@<code>{C}の@<code>{A}からの距離は@<code>{2}となります。
今回、入力される側のローターは@<code>{A}に設定されているため、@<code>{A}から@<code>{2}の距離の@<code>{C}に入力がいくように思えます。
実際に動かしてみると、次のようになります。

//image[rotor_rotor_3][Aに設定したローターに、Bに設定したローターからCを入力][scale=0.4]{
//}

プラグボードの入力した文字はAからの距離の数字として扱われ、ローターに設定された文字にその距離が足された場所の文字がローターの中での入力になるという法則は、
@<b>{今回は成り立っておりません}。
どういう仕組みか探るために、今度は送信される@<code>{C}を固定しつつ送信するローター側の設定を変えていき、受け取るローター側でどういうinputになるのかを見て行きます。

//table[plguboard_rotor_table_c_num][Cを送信するローター側の設定をいろいろ変えてみる]{
送信する側のローターの設定	A	B	C	D	E	F	~
-------------------------------------------------------------
送信する側の設定からCへの距離	2	1	0	-1	-2	-3	~
受け取るローターでのinput	C	B	A	Z	X	Y	~
受け取るローターでのoutput	W	Y	Z	A	B	C	~
//}

@<table>{plguboard_rotor_table_c_num}を見ていくと、法則が見えてきます。
@<b>{一つ前のローターから送られた文字はそのローターの設定値からの距離の数字（以降はオフセットと呼びます）として扱われ、ローターに設定された文字にその距離が足された場所の文字がローターの中での入力になる}。

@<img>{rotor_rotor_3}では、送信するローターに設定されている文字は@<code>{B}です。
@<code>{C}を送信するので、その距離は@<code>{1}です。
@<code>{C}、すなわち@<code>{1}を受信したローターでは@<code>{A}が設定されているため、そのインプットは@<code>{A}に@<code>{1}を足した@<code>{B}と同様の結果となります。

//image[rotor_rotor_3_2][1のインプットとなる]{
//}

=== 連結している次の装置から返ってきた文字をどう扱うのか

連結している次の装置から返ってきた文字をどう扱うのかも考えていきましょう。
ただ、これは今までとまったく同じで、処理の流れが逆なだけです。

//image[rotor_rotor_4][Bに設定された次の装置からBが返却される][scale=0.4]{
//}

ここでも@<b>{設定されている文字に一つ前のローターのオフセットを足したものが換字の入力となる}法則が成り立っていることがわかります。

== コードに落としていく

今までのことを総合すると、ローターは@<code>{オフセット}を受け取って（以降はオフセットと呼びます）、自身の持ってる換字表で換字し、次の装置へ@<code>{オフセット}を送信します。
そして、次の装置から@<code>{オフセット}を受け取って、また換字表を裏から換字し、前の装置へ@<code>{オフセット}を返却します。
これがローターの全てです。

//image[rotor_model][ローターの仕組み][scale=0.4]{
//}

これらを実際にコードに落としていきます。
真っ先にローターからではなく、その周りからモデリングして行きましょう。

=== アルファベット

今回は文字に数字を足して別の文字を指したり、@<code>{Z}に@<code>{1}を足したら@<code>{A}になるなどの仕様があります。
また@<code>{A}から@<code>{Z}の26個の大文字のアルファベットのみという制限もあります。
これをモデリングします。
まずは 単純に文字列を持つだけのクラスにします。
@<code>{A}から@<code>{Z}の26個の大文字のアルファベットでない場合は例外を投げるようにします。

//list[alphabet_model][アルファベットを定義]{
data class Alphabet(val char: Char) {

  init {
    if (!ALL.contains(char))
      throw IllegalArgumentException("not uppercase alphabet")
  }

  companion object {
    val ALL =
      "ABCDEFGHIJKLMNOPQRSTUVWXYZ".toCharArray()
  }
}
//}

また、今回は@<code>{A}であれば@<code>{0}でもあるように、アルファベットを数字でも表現します。

 * 数字を受け取るコンストラクタを用意する
 * 数字を取得できるようにする
 * 文字と文字の距離を測れるようにする

これらをコードに落とし込んで、下記のようにします。
これで完成です。

//list[alphabet_num][数字にも対応]{
data class Alphabet(val char: Char) {

  constructor(pos: Int) : this(ALL[adjust(pos)])

  init {
    if (!ALL.contains(char))
      throw IllegalArgumentException("not uppercase alphabet")
  }

  companion object {
    val ALL =
      "ABCDEFGHIJKLMNOPQRSTUVWXYZ".toCharArray()
    private val COUNT_OF_ALL = ALL.size

    private fun adjust(pos: Int): Int {
      var adjusted = pos
      while (adjusted !in 0..(COUNT_OF_ALL - 1)) {
        if (adjusted < 0) {
          adjusted += COUNT_OF_ALL
        } else {
          adjusted -= COUNT_OF_ALL
        }
      }
      return adjusted
    }
  }

  fun pos(): Int = ALL.indexOf(char)

  fun diff(alphabet: Alphabet): Int = pos() - alphabet.pos()
}
//}

=== 換字表

次にローターの内部で持っている換字表をモデリングしていきます。
実際はA~Zが他の文字へ配線されています。
それにちなんで名前は@<code>{WiringTable}としましょう。
たとえば、今まで使ってた換字表の@<code>{ZYXWVUTSRQPPNMLKJIHGFEDCBA}をコンストラクタに渡すようにします。
初期化時に、文字に漏れがなくダブりがないことを確認しています。

//list[wiring_table][WiringTableを定義]{
class WiringTable(
  charArray: CharArray
) {

  companion object {
    val NORMAL = WiringTable("ABCDEFGHIJKLMNOPQRSTUVWXYZ".toCharArray())
  }

  val alphabets = charArray.map { Alphabet(it) }

  init {
    if (
      !charArray.all { Alphabet.ALL.contains(it) } ||
      charArray.size != Alphabet.ALL.size
    ) throw RuntimeException("invalid writing table")
  }
}
//}

換字機能は、@<code>{ABCDEFGHIJKLMNOPQRSTUVWXYZ}から@<code>{ZYXWVUTSRQPPNMLKJIHGFEDCBA}で換字する場合と、
逆に@<code>{ZYXWVUTSRQPPNMLKJIHGFEDCBA}から@<code>{ABCDEFGHIJKLMNOPQRSTUVWXYZ}に換字する場合とがあります。
これらもメソッドとして用意してあげれば完了です。

//list[substitution][換字機能を実装]{

  fun frontToBack(alphabet: Alphabet): Alphabet =
    alphabets[NORMAL.alphabets.indexOf(alphabet)]

  fun backToFront(alphabet: Alphabet): Alphabet =
    NORMAL.alphabets[alphabets.indexOf(alphabet)]

//}

==={rotor_model} ローター

では、本章の目的でもあるローターの仕様をコードに落としていきましょう。
まず、ローターは換字表である@<code>{WiringTable}を必ず一つ持っています。

//list[rotor_constructor][WiringTableをコンストラクタで受け取る]{
class Rotor(
  private val wiringTable: WiringTable
)
//}

そして、ローターには@<code>{A}や@<code>{B}などのオペレータがダイアルを回して設定する@<b>{設定値}という概念があります。

//list[rotor_initial_setting][初期設定値を設定できるようにする]{
class Rotor(
  private val wiringTable: WiringTable
) {

  private var initialSetting = 0

  fun setInitialPosition(initialPosition: Int) {
    this.initialSetting = initialPosition
  }

}
//}

ローターには次の装置として、ローターもしくはリフレクターを結合することができます。
どちらも換字する装置であるため、これを@<code>{Converter}というインタフェースで定義し、
ローターおよびリフレクターはこれを実装するようにします。

//list[rotor_connect_converter][ローターはConverterと結合できる]{
class Rotor(...): Converter {
  ...
  private var next: Converter? = null

  fun connect(next: Converter) {
    this.next = next
  }
}
//}

本章の冒頭で触れただけなので、お忘れの方も多くいるかもしれませんが、下記の仕様もあります。

 * 一つ前に連結しているプラグボードやローターから、あるタイミングで1メモリ進められる
 * 自身が26メモリ進む（1回転する）と、自身に連結してる次のローターを1メモリ進める

//list[rotor_tick][ローターは1メモリ進めるメソッドを持っている]{
class Rotor(...): Converter {
  ...

  private var tickCount = 0
  private var next: Converter? = null
  ...

  override fun tick() {
    val next = next ?: throw RuntimeException("not found next")
    tickCount = (tickCount + 1) % wiringTable.alphabets.size
    if (tickCount == 0) {
      next.tick()
    }
  }
}
//}

最後に、要である換字の機能を実装していきましょう。
@<code>{オフセット}を受け取って（以降はオフセットと呼びます）、自身の持ってる換字表で換字し、
次の装置へ@<code>{オフセット}を送信する部分（@<img>{rotor_model_2} の左部分）を@<code>{frontToBack}メソッド、
そして@<img>{rotor_model_2} の右部分を@<code>{backToFront}メソッドとして、
全体を@<code>{convert}メソッドと表現してみます。

//image[rotor_model_2][ローターのモデル][scale=0.4]{
//}

コードはこのようになります。

//list[rotor_converter][converterメソッド]{
class Rotor(...): Converter {
  ...
  override fun convert(offset: Int): Int {
    val next = next ?: throw RuntimeException("not found next")
    val offsetForNext = frontToBack(offset)
    val returnByNext = next.convert(offsetForNext)
    return backToFront(returnByNext)
  }

  private fun frontToBack(offset: Int): Int {
    val setting = Alphabet(initialSetting + tickCount)
    // オフセットをもらって、どの文字が input になるのか決める
    val input = setting.plus(offset)
    // 換字する (frontToback)
    val cyphering = wiringTable.frontToBack(input)
    // 換字して得た文字と設定値の距離をオフセットとして送る
    return cyphering.diff(setting)
  }

  private fun backToFront(offset: Int): Int {
    val setting = Alphabet(initialSetting + tickCount)
    // オフセットをもらって、どの文字が input になるのか決める
    val input = setting.plus(offset)
    // 換字する (backToFront)
    val cyphering = wiringTable.backToFront(input)
    // 換字して得た文字と設定値の距離をオフセットとして送る
    return cyphering.diff(setting)
  }
}
//}

これでRotorクラスは完成です。
コードの全体像は @<href>{https://github.com/kgmyshin/enigma-simulator} から確認できます。
