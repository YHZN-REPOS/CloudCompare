# CloudCompare (Personal Extended Version)

本项目基于开源点云处理软件 [CloudCompare](https://cloudcompare.org) 进行开发与功能增强。

## 项目说明
本项目继承自 CloudCompare 官方版，旨在优化点云处理流程，特别是针对标量场（Scalar Fields）的选择与赋值操作进行了深度定制。

## 新增功能
### 1. 标量场选择与赋值工具 (SF Selection Tool)
一种全新的交互式工具，允许用户在可视化界面中直接框选点云区域并分配标量场数值。
- **启动路径**：菜单栏 `Edit > Scalar fields > SF Selection Tool`
- **主要特性**：
    - 支持矩形和多边形选区（默认为多边形）。
    - 自动探测选区内现有的标量值。
    - 快捷键 `S`：选区完成后直接弹出赋值对话框。
    - 自动闭合选区，操作更流畅。

## 编译指南 (macOS M1/M2/M3)
本项目针对搭载 Apple Silicon 芯片的 Mac 进行了优化，并使用 `pixi` 管理依赖 and 环境，大大简化了编译流程。

1. **安装 Pixi**: `curl -fsSL https://pixi.sh/install.sh | bash`
2. **下载依赖并编译**: `pixi run build`
3. **安装与运行**: `pixi run CloudCompare`

详细编译细节请参考：[doc/M1_Build_Guide.md](doc/M1_Build_Guide.md)

## 本项目文档索引
您可以查阅以下文档以获得更多详细信息：

| 文档名称 | 内容说明 |
| --- | --- |
| [M1_Build_Guide.md](doc/M1_Build_Guide.md) | **M1 编译与运行指南**：详细的构建步骤与环境配置。 |
| [SF_Tool_Manual_CN.md](doc/SF_Tool_Manual_CN.md) | **标量场工具中文手册**：新工具的使用方法、快捷键及常见问题。 |
| [SF_Tool_Walkthrough.md](doc/SF_Tool_Walkthrough.md) | **技术总结报告**：记录了功能实现的技术细节、代码修改点及 Bug 修复过程。 |

## 开源协议
本项目遵循原项目的 **GPL v3.0** 开源协议。
