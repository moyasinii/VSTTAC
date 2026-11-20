# preamp-plugin

名機マイクプリアンプ（Neve 1073 のプリアンプ部）を回路図から学び、VST プラグインとして再現する学習プロジェクト。

## ロードマップ

- [ ] Phase 1: Python で「マイクプリらしい音」の要素（トランス特性・飽和・倍音）を試す
- [ ] Phase 2: 回路図をブロックに分けて読み解く
- [ ] Phase 3: 回路定数にもとづくモデルに置き換える
- [ ] Phase 4: JUCE (C++) で VST3 プラグイン化

## フォルダ構成

- `python/` … Phase 1〜3 のプロトタイプ用スクリプト

## 使い方（Phase 1）

```
pip install numpy scipy matplotlib soundfile
cd python
python first_test.py
```

`python/` に `input.wav` を置いてから実行すると、`output.wav` が書き出されます。
音声ファイルは `.gitignore` でリポジトリに含めないようにしています。

## 注意

個人の学習目的のプロジェクトです。公開・配布する場合、製品名に他社の商標は使用しません。
