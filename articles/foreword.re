= まえがき

== なぜ本書を書くことにしたのか

2018年の年末、筆者はNetflixでSHERLOCKというドラマにがっつりはまっておりました。
ベネディクト・カンバーバッチ演じるシャーロック・ホームズの魅せる推理は面白く、気づけば全話を視聴し終わっておりました。
謎解き熱が冷めない筆者にNetflixが次に勧めてきた映画は、
またもやベネディクト・カンバーバッチが主演の@<b>{イミテーション・ゲーム／エニグマと天才数学者の秘密}でした。
この映画のあらすじを一言で言うと@<b>{アラン・チューリングが第二次世界大戦中にドイツ軍の使用するエニグマの暗号をどうやって解読したのか}という話です。
アラン・チューリングはコンピュータの元になるチューリング・マシンという概念を考えた人物です。
そのチューリングがどのようにエニグマを解読したのか。
まだ見てない方はぜひご覧ください。
特にエンジニアは楽しめる作品になっていると思います。
兎にも角にも、筆者はこの作品にのめり込んでしまいました。
そして気づいたら本書の題材であるエニグマのシミュレータを作っていた。
さらに、技術書典も近いのでそのことを本にしてみようと思ったのが経緯です。

== 本書のゴール

本書ではゴールを@<b>{エニグマをソフトウェアシミュレーションするプログラムを書くこと}としています。
本来であれば、アラン・チューリングが解析に使用した@<b>{ボンベ}もプログラムに落とし込みたかったのですが、
時間がなかったため今回は対象外とさせて頂きました。
また機会がある時に挑戦します。

== 使用言語

本書では例として乗せているコードに Kotlin を使用しております。
