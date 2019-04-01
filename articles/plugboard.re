= プラグボード

プラグボードはキーボードから入力された文字の一部を、
ローターに送る前に別の文字に変更する装置です@<img>{plugboard}@<fn>{plugboard_cc}。

#@# 全体像の画像

== プラグボードとは

プラグボードの外観がこちらです。

//image[plugboard][プラグボード by Bob Lord]{
//}

//footnote[plugboard_cc][enigma plugboard by Bob Lord https://en.wikipedia.org/wiki/Enigma_machine#/media/File:Enigma-plugboard.jpg]

このプラグボードでは@<code>{A}と@<code>{J}、また@<code>{S}と@<code>{O}が繋がれていることがわかると思います。
これによって、@<code>{A}の入力は@<code>{J}に、@<code>{J}の入力は@<code>{A}に変換されます。
ローターやリフレクターに比べると簡単な構造ですが、これがあることによってエニグマを解読することがより困難になります。

== コードに落としていく

プラグボードをコードに落としていきましょう。

=== 配線テーブル

プラグボードの配線テーブルは任意のペアを作ることで実現されます。
リフレクターでは全ての文字がペアになっていましたが、プラグボードの配線はその制限がありません。
@<code>{WritingTable}というクラス名にします。

//list[wiring_table][WiringTableを定義]{
class WiringTable(
  private val map: Map<Char, Char>
) {

  companion object {
    private val LETTERS = "ABCDEFGHIJKLMNOPQRSTUVWXYZ".toCharArray()
  }

  init {
    if (
      !map.map { listOf(it.key, it.value) }.flatten().all { LETTERS.contains(it) }
    ) throw RuntimeException("invalid writing table")
  }
}
//}

コンストラクタでは任意のペアのマップを受け取るようにしています。
初期化時には、@<b>{全ての文字が大文字の英語であること}だけを確認しています。

ここに文字を変換するメソッドを追加しておきます。変換しない場合は、元の文字をそのまま使います。

//list[convert_if_needed][変換するメソッド]{
  fun convertIfNeeded(char: Char): Char {
    map.entries.forEach {
      if (it.key == char) {
        return it.value
      }
      if (it.value == char) {
        return it.key
      }
    }
    return char
  }
//}

==={plugboard-model} プラグボード

まずは、@<code>{WiringTable}をコンストラクタで受け取ります。

//list[constructor][コンストラクタ]{
class Plugboard(
  private val wiringTable: WiringTable
)
//}

プラグボードは、後ろにローターが接続されます。

//list[connect_rotor][ローターと接続する]{
class Plugboard(
  private val wiringTable: WiringTable
) {
  private var next: Rotor? = null

  fun connect(next: Rotor) {
    this.next = next
  }
}
//}

最後に、受け取った文字列をローターに渡して、ローターから受け取った文字列を配線テーブルを通してから返却するメソッドを用意します。
変換する際には、必ずローターを1メモリ進めます。

//list[convert][変換メソッド]{
class Plugboard(...) {
  ...
  fun convert(char: Char): Char {
    val next = next ?: throw RuntimeException("not found rotor")
    next.tick()
    val sendToNext = wiringTable.convertIfNeeded(char).let { Alphabet(it) }
    val returnByNext = Alphabet(next.convert(sendToNext.pos()))
    return wiringTable.convertIfNeeded(returnByNext.char)
  }
}
//}

これでプラグボードの実装は完了です。
