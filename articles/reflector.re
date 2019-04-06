= リフレクター

エニグマは複合機能を持っています。
それを実現しているのが、このリフレクターという装置です。
本章では、このリフレクターがどのようにして複合機能を実現しているのかの理解を深めていきます。
そして、またプログラムに落としていきましょう。

#@# TODO: 全体像の画像

== 複合機能について

リフレクターはA~Zの26文字全てが2文字のペアになるように配線されています。
例えば、@<code>{B}と@<code>{V}がペアになっているとします。
@<code>{B}に入力があれば、@<code>{V}が出力されます。

//image[reflector_1][Bに入力があったら、Vを出力する][scale=0.4]{
//}

またペアになっているので、逆に@<code>{V}に入力があれば、@<code>{B}が出力されます。

//image[reflector_2][Vに入力があったら、Bを出力する][scale=0.4]{
//}

この反転性がエニグマに複合機能をもたらしています。
このリフレクター単体でも複合機能はあります。
例えば@<code>{ABC}と入力すれば@<code>{DVG}などと出力され、
そしてその出力の@<code>{DVG}を入力すれば@<code>{ABC}が出力されることはわかりやすいと思います。
では、ここにローターを組み合わせた場合はどうなるでしょうか。

ローターに@<code>{E}の入力を渡すと、リフレクターを通りローターに戻って、最終的に@<code>{Y}の出力がありました。

//image[reflector_rotor_1][ローターとリフレクター①][scale=0.4]{
//}

この状態の時に@<code>{E}ではなくて@<code>{Y}の入力を与えると、@<code>{E}が出力され反転していること、複合できていることがわかります。

//image[reflector_rotor_2][ローターとリフレクター②][scale=0.4]{
//}

ローター自体には反転性はありません。
しかし、@<b>{表}から@<code>{E}の入力をして、@<code>{V}が出力される時、
その逆、つまり@<b>{裏}から@<code>{V}を渡すと@<code>{E}が出力されることは確定しています。

//image[rotor][ローターの表と裏][scale=0.8]{
//}

この性質とリフレクターの性質を合わせると、ローターが含まれても複合することが可能になることがわかると思います。
つまるところ、入力・出力の方向性は関係なく、リフレクターの存在によって全ての文字はペアっているのです。

//image[reflector_rotor_3][方向は関係なく、EとYがペアになっている][scale=0.4]{
//}

== コードに落としていく

リフレクターをコードに落としていきましょう。

=== 配線テーブル

リフレクターではA~Zの26文字が13個のペアとなって配線されています。
これをそのままコードに落とし込みましょう。
@<code>{WiringTable}というクラス名にします。

//list[wiring_table][WiringTableを定義]{
class WiringTable(
  private val map: Map<Char, Char>
) {

  companion object {
    private val LETTERS = "ABCDEFGHIJKLMNOPQRSTUVWXYZ".toCharArray()
  }

  init {
    if (
      !map.map { listOf(it.key, it.value) }.flatten().all { LETTERS.contains(it) } ||
      map.size != (LETTERS.size / 2)
    ) throw RuntimeException("invalid wiring table")
  }
}
//}

コンストラクタでは、13個のサイズのマップを受け取るようにしています。
初期化時に@<b>{すべての文字が過不足なくあること}を確認しています。

ここにペアの文字を取得するメソッドを追加しておきます。

//list[wiring_table_pair][pairを取得]{
class WiringTable(
  private val map: Map<Char, Char>
) {
  ...
  fun pair(char: Char): Char {
    map.entries.forEach {
      if (it.key == char) {
        return it.value
      }
      if (it.value == char) {
        return it.key
      }
    }
    throw IllegalArgumentException("not found")
  }
//}

これで、@<code>{WiringTable}の実装は完了です。

==={reflector-model} リフレクター

リフレクターを実装します。
ローターからは、@<code>{A}を@<code>{0}とした場合のオフセットを受け取り、@<code>{WiringTable}からペアを取得し、そのペアのオフセットを返却します。
コードは次のようになります。

//list[reflector][Reflector]{
class Reflector(
  private val wiringTable: WiringTable
) : Converter {

  override fun convert(offset: Int): Int {
    val input = Alphabet(offset)
    return Alphabet(wiringTable.pair(input.char)).pos()
  }
}
//}

これでリフレクターの実装は完了です。
