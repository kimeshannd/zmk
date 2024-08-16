module.exports = {
  docs: [
    {
      type: "category",
      label: "Getting Started",
      link: {
        type: "doc",
        id: "intro",
      },
      collapsed: false,
      items: [
        "hardware",
        "faq",
        "user-setup",
        "customization",
        {
          type: "category",
          label: "Troubleshooting",
          link: {
            type: "doc",
            id: "troubleshooting/index",
          },
          collapsed: true,
          items: [
            "troubleshooting/building-issues",
            "troubleshooting/flashing-issues",
            "troubleshooting/connection-issues",
          ],
        },
      ],
    },
    {
      Features: [
        "features/bluetooth",
        "features/modules",
        "features/split-keyboards",
        "features/debouncing",
        "features/battery",
        "features/soft-off",
        "features/displays",
        "features/backlight",
        "features/underglow",
      ],
    },
    {
      type: "category",
      label: "Keymaps",
      link: {
        type: "doc",
        id: "keymaps/index",
      },
      collapsed: true,
      items: [
        {
          type: "category",
          label: "Behaviors",
          link: {
            type: "doc",
            id: "keymaps/behaviors/index",
          },
          collapsed: true,
          items: [
            "keymaps/behaviors/key-press",
            "keymaps/behaviors/layers",
            "keymaps/behaviors/misc",
            "keymaps/behaviors/hold-tap",
            "keymaps/behaviors/mod-tap",
            "keymaps/behaviors/mod-morph",
            "keymaps/behaviors/macros",
            "keymaps/behaviors/key-toggle",
            "keymaps/behaviors/sticky-key",
            "keymaps/behaviors/sticky-layer",
            "keymaps/behaviors/tap-dance",
            "keymaps/behaviors/caps-word",
            "keymaps/behaviors/key-repeat",
            "keymaps/behaviors/sensor-rotate",
            "keymaps/behaviors/mouse-emulation",
            "keymaps/behaviors/reset",
            "keymaps/behaviors/bluetooth",
            "keymaps/behaviors/outputs",
            "keymaps/behaviors/underglow",
            "keymaps/behaviors/backlight",
            "keymaps/behaviors/power",
            "keymaps/behaviors/soft-off",
          ],
        },
        "keymaps/modifiers",
        "keymaps/combos",
        "keymaps/conditional-layers",
        "keymaps/encoders",
        "keymaps/list-of-codes",
      ],
    },
    {
      type: "category",
      label: "Configuration",
      link: {
        type: "doc",
        id: "config/index",
      },
      collapsed: true,
      items: [
        "config/backlight",
        "config/battery",
        "config/behaviors",
        "config/bluetooth",
        "config/combos",
        "config/displays",
        "config/encoders",
        "config/keymap",
        "config/kscan",
        "config/power",
        "config/underglow",
        "config/system",
      ],
    },
    {
      Development: [
        "development/clean-room",
        "development/pre-commit",
        "development/documentation",
        {
          type: "category",
          label: "Setup",
          link: {
            type: "doc",
            id: "development/setup/index",
          },
          collapsed: true,
          items: ["development/setup/docker", "development/setup/native"],
        },
        "development/build-flash",
        "development/boards-shields-keymaps",
        "development/posix-board",
        "development/tests",
        "development/usb-logging",
        "development/ide-integration",
        "development/studio-rpc-protocol",
        {
          type: "category",
          label: "Guides",
          collapsed: false,
          items: [
            "development/new-shield",
            "development/hardware-metadata-files",
            "development/new-behavior",
          ],
        },
      ],
    },
  ],
};
