= エニグマとは

エニグマとは、第二次世界大戦でドイツ軍で使用されていたローター式の暗号機です。

//image[enigma][エニグマ][scale=0.4]{
//}
#@# パブリックドメイン https://ja.wikipedia.org/wiki/%E3%83%95%E3%82%A1%E3%82%A4%E3%83%AB:EnigmaMachineLabeled.jpg

== エニグマの使い方

エニグマは任意の設定をした後に、暗号化したい文字列をキーボードにタイピングしていきます。
１文字１文字タイピングするごとに、ランプボードで暗号化された結果の文字が１文字１文字光ります。
光った文字列を繋げれば暗号化された文字列の完成です。
ここでは例えば、オペレーターが@<code>{HELLO}とタイピングして、ランプボードは順に@<code>{MFNAB}が光ったとします。

ではこの@<code>{MFNAB}を複合していきましょう。
複合する手法は、とても簡単です。
まずは、エニグマを@<code>{HELLO}とタイピングしはじめた時の設定にします。
そして@<code>{MFNAB}とタイピングするだけで、ランプボードは@<code>{HELLO}が点滅するのです。
つまり、暗号化された文字列を複合するには@<b>{暗号化に使った設定値だけ}を知っていれば複合できるのです。

== エニグマの構造を簡単に

エニグマは、以下の主にパーツからなっています。

 * キーボード
 * プラグボード
 * ローター
 * リフレクター
 * ランプボード

キーボードはオペレータの入力機器で、ランプボードは暗号化された文字を出力する機器です。
そして、それ以外の@<b>{プラグボード}、@<b>{ローター}、@<b>{リフレクター}は文字を暗号化もしくは複合化するための装置です。
下記が入力された文字がどのように変換され、最終的にランプボードにたどり着くのかを示した簡単な図です。

//image[construction][構造][scale=0.4]{
//}

各装置については別の章で詳しく触れるのですが、キーボードから入力された文字は、プラグボード -> ローター（×3） -> リフレクターを通りながら変換されていき、
またリフレクター -> ローター（×3） -> プラグボード の順で戻りながらここでも変換されてきてランプボードにたどり着きます。
１文字１文字タイプするたびにローターが回転することで、同じ文字を入力しても同じ出力にならないようになっています。
さきの@<code>{HELLO}の中の@<code>{LL}の部分が@<code>{NA}に変換されているのがいい例です。

== 設定値

前節では@<b>{任意の設定をして}という書き方をしましたが、実際のローターの主な設定値は次の通りです。

 * ローターの並び順
 ** ローターには中の配線が違うものが数種類あり、その数種類を並び替えて使います
 * ローターの設定
 ** それぞれのローターの初期設定で、ローターを回転して設定します
 * プラグボード
 ** どの文字とどの文字を入れ替えるか

次章からこの設定の仕方含め@<b>{ローター}、@<b>{リフレクター}、@<b>{プラグボード}について、詳しく見ていきながら
プログラムに落としてみるということに挑戦していきます。
