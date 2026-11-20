# first_test.py
# 環境チェック兼、はじめての「サチュレーション」実験
# input.wav を読み込み、やわらかく歪ませて output.wav に書き出します

import numpy as np
import soundfile as sf
import matplotlib.pyplot as plt

plt.rcParams["font.family"] = "Meiryo"  # Windows でグラフに日本語を表示するため

# ---- 設定 ----
DRIVE = 4.0   # 歪みの強さ。1.0でほぼ素通し、大きくするほど歪む

# ---- 読み込み ----
x, sr = sf.read("input.wav")
print(f"サンプルレート: {sr} Hz / 長さ: {len(x) / sr:.1f} 秒")

# ---- 処理：tanh によるソフトクリップ ----
# tanh は大きい入力ほどなめらかに頭打ちになる関数で、
# アナログ機器の「飽和」をまねる一番シンプルな方法です
y = np.tanh(DRIVE * x) / np.tanh(DRIVE)

# ---- 書き出し ----
sf.write("output.wav", y, sr)
print("output.wav を書き出しました")

# ---- 入出力カーブのグラフ ----
v = np.linspace(-1, 1, 500)
plt.plot(v, v, "--", label="素通し")
plt.plot(v, np.tanh(DRIVE * v) / np.tanh(DRIVE), label=f"tanh (DRIVE={DRIVE})")
plt.xlabel("入力")
plt.ylabel("出力")
plt.title("入出力カーブ")
plt.legend()
plt.grid(True)
plt.show()
