========================================================================
       DocuWorks 8.0用プラグイン : SimpleSplitter v.1.2
========================================================================

　これは、富士ゼロックス株式会社のDocuWorks 8.0 に機能を追加するプラグインソフトウェアです。このソフトウェア単独では動作しません。

1. 概要

　一つ一つはページ数が少ないけれど、数がたくさんある紙文書をスキャンしてDW化する場合はどうしています。一つづつ分けてはスキャンを繰り返すのは面倒です、まとめてどかっと一気に全部をスキャンすれば、...でも、その後で個別に切り分けるのはどうしましょ。
　というわけでできたのがこのプラグインです。付箋で印をつけておくと、その場所で切り分けてその付箋に書かれた名前のDW文書に作ります。

2. インストール

2.1 前バージョンからのアップデート

　このプラグインの前バージョンを利用していた場合は、いったん「プラグインツールバー」から「簡易文書分割」を削除してください。
　DocuWorks デスクを開き、「プラグイン(T)」メニューにある「設定(S)...」コマンドを選んで「プラグインの設定」ダイアログを開きます。右側の「現在のプラグインメニュー(M)」の中に「簡易文書分割」があるので、それを選んで「削除(R)」ボタンをクリックします。「閉じる」をクリックしてダイアログを閉じます。
DocuWorksデスクを閉じます。
　あとは、「2.2　新規のインストール」と同じ手順で古いファイルを新しいファイルで置き換えてください。

2.2 新規のインストール
　このプラグインはDocuWorks 8.0用です。DocuWorks 6.0用プログラムをdwsdk805でビルドしなおしたものですので DW6.0以降で動作すると思われますが確認はしていません。
、このソフトウェアは、富士ゼロックス株式会社の「DocuWorks(TM) Development Tool Kit 6.0.0」、「DocuWorks Development Tool Kit 日本語版　バージョン８」を用いて作成されています。

　次に、SimpleSplitter.dll を <DocuWorksインストールディレクトリ>\bin\plugins\ ( 通常は、C:\Program Files (x86)\Fuji Xerox\DocuWorks\bin\plugins\ )の下にコピーします。　

  このプラグインを使用するには、DocuWorks Deskを起動します。次に、DocuWorks Deskの[ツール]>[ツールの設定...]メニューでツールバーの設定ダイアログを開き、分類でツールを選ぶとコマンドに表示される「簡易文書分割」をDocuWorks Deskのツールバーにドラッグしてツールバーに追加します。
  設定項目については、「3.2 設定項目」を参照してください。

3. 機能

3.1 使用方法
　まず、分割したい文書を開いて、取り出したい部分のそれぞれの最初のページに<緑色>の付箋を張り付けます。そして付箋に取り出した文書に付ける名前を書きこみます。付箋の色は必ず<緑色>にしてください。他の色は無視されます。
　普通は最初のページに最初の<緑色>の付箋を付けることになるでしょう。もし、最初のページに<緑色>の付箋が無ければ、<緑色>の付箋が現れるまでのページは不要な物として無視されます。もし、文書の途中に不要なページあるならば、不要な部分の最初のページにファイル名を書いていない<緑色>の付箋を付けます。
　このようにして付箋で分割場所とファイル名を指定した文書を選択し、プラグイン(T）メニューから「簡易文書分割」を選びます。すると、その文書と同じ名前のフォルダが作成され、そのフォルダの中に付箋で印を付けた場所で切り分けてできた文書ができます。
「表示(V)」メニューの「最新の情報に更新(R)...」から「現在開いているフォルダの下すべて(R)...」を実行してください。左のファイルツリーのペインが更新されて新しくフォルダができていることがわかるでしょう。
もし、文書名と同じ名前のフォルダが既に存在しているエラーになってその文書はスキップします。なお、元のDocuWorks文書はそのままで残っています。

3.2 設定項目

  「元文書と同一の場所に出力する」
	これがチェックされていると、新規にフォルダを作成してそこに分割するのではなく、元文書と同じフォルダに分割した文書を生成します。デフォルトではオフ。
　「元文書は削除する」
	これがチェックされていると、ファイル分割をした後に元文書を削除します。削除された元文書はWindowsの「ごみ箱」に入ります。DocuWorksデスクの「ごみ箱」ではないので注意してください。ファイル分割に失敗した場合は削除しません。デフォルトではオフ。
　「#を通し番号で置き換える」
	これがチェックされていると、付箋で指定されたファイル名の # (半角の#ですので注意してください) を通し番号に置き換えて使います。例えば、どの付箋にも「付録#」と指定しておくだけで、「付録1.xdw」、「付録2.xdw」、「付録3.xdw」という具合になります。
　「初期値」、「桁数」
	通し番号の初期値と桁数です。数値が桁数に満たない場合は、例えば 007 の様に先頭に0を加えて指定された桁数にします。桁数が足りない場合は無視されます。例えば、初期値が1234で桁数が3桁だと、1234 が値になります。
　「文書をまたがる」
	これがチェックされていると、次に「簡易文書分割」をする時にも通し番号が引き継がれます。これがチェックされていない場合は、分割する文書ごとに通し番号が初期値にリセットされます。（注意：複数文書を選択して処理する場合、どの順序で処理されるかは決まっていません。順番を気にする場合は、文書を一つずつ処理してください。）

4. その他

　このソフトウェアは、富士ゼロックス株式会社の「DocuWorks(TM) Development Tool Kit 6.0」を用いて作成されています。

　このソフトウェアは、MITライセンスの元に提供されます。
--------------------------------------------------------------------------------------------------
MIT License

Copyright (c) 2002,2005,2017 sagamiya

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
--------------------------------------------------------------------------------------------------
2017年 3月 3日 算譜渡世　相模屋

変更履歴
v1.2    2017.3.3   MITライセンスへ変更。
v1.1	2005.7.3   機能改善: ファイル名の指定に、改行、タブ、空白がある場合、途中のタブは空白に、改行は無視、はじめや終わりにある空白、タブ、改行も無視するよう修正。従来は、タブや改行があるとエラーになていた。なお、ファイル名として >や<といった使用できない文字があった場合は、従来と同じで実行時にエラーを表示して中止する。
v1.0	2005.1.23  機能拡張: 「元文書と同一の場所に出力する」「元文書は削除する」「#を通し番号で置き換える」「初期値」「桁数」「文書をまたがる」の機能を追加。
v0.2	2002.10.21 不具合修正：作業用の一時ファイル名がハードコーディングされていたため、Cドライブにtempというディレクトリが無いとエラーが発生する不具合を修正。
v0.1	2002.10.20 初版リリース
