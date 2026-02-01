# CloudCompare M1 (Apple Silicon) 编译与运行指南

本指南详细说明了如何在搭载 Apple Silicon (M1/M2/M3) 芯片的 macOS 系统上使用 `pixi` 环境编译和运行 CloudCompare。

## 1. 环境准备

本项目使用 [pixi](https://pixi.sh/) 作为包管理器和构建工具，它会自动处理 Qt6、CMake、Ninja 以及所有的依赖库（如 PCL, PDAL, OpenCV 等）。

如果您还没有安装 `pixi`，可以通过以下命令安装：
```bash
curl -fsSL https://pixi.sh/install.sh | bash
```

## 2. 编译步骤

在项目根目录下，执行以下命令：

### A. 配置环境 (Configure)
此步骤会下载依赖并生成 CMake 构建文件。
```bash
pixi run configure
```

### B. 编译 (Build)
使用 Ninja 进行多线程编译。
```bash
pixi run build
```

### C. 安装 (Install)
将编译好的二进制文件安装到 `.build/install` 目录，并处理必要的 RPath。
```bash
pixi run install
```

---

## 3. 启动指令

您可以直接通过 `pixi` 命令启动，或者定位到安装后的 `.app` 包。

### 方法一：直接使用 pixi 启动（推荐）
```bash
pixi run CloudCompare
```

### 方法二：打开安装后的应用包
```bash
open .build/install/CloudCompare/CloudCompare.app
```

---

## 4. 常用维护指令

| 指令 | 说明 |
| --- | --- |
| `pixi run clean` | 清理构建生成的中间文件 |
| `pixi run build && pixi run install` | 组合指令：编译完成后立即安装 |
| `pixi task list` | 查看所有可用的 pixi 任务 |

## 5. 注意事项
- **架构确认**：本配置专门针对 `osx-arm64` 平台优化。
- **首次编译**：初次编译可能需要较长时间，因为需要下载大量的依赖包（约几百MB）。
- **RPath 问题**：如果在启动时提示找不到库，通常是因为没有执行 `pixi run install` 步骤，该步骤会自动修复库的链接路径。
