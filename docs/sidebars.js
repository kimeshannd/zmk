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
        "features/keymaps",
        "features/bluetooth",
        "features/split-keyboards",
        "features/combos",
        "features/conditional-layers",
        "features/debouncing",
        "features/displays",
        "features/encoders",
        "features/modules",
        "features/underglow",
        "features/backlight",
        "features/battery",
        "features/soft-off",
      ],
    },
    {
      type: "category",
      label: "Behaviors",
      link: {
        type: "doc",
        id: "behaviors/index",
      },
      collapsed: true,
      items: [
        "behaviors/key-press",
        "behaviors/layers",
        "behaviors/misc",
        "behaviors/hold-tap",
        "behaviors/mod-tap",
        "behaviors/mod-morph",
        "behaviors/macros",
        "behaviors/key-toggle",
        "behaviors/sticky-key",
        "behaviors/sticky-layer",
        "behaviors/tap-dance",
        "behaviors/caps-word",
        "behaviors/key-repeat",
        "behaviors/sensor-rotate",
        "behaviors/mouse-emulation",
        "behaviors/reset",
        "behaviors/bluetooth",
        "behaviors/outputs",
        "behaviors/underglow",
        "behaviors/backlight",
        "behaviors/power",
        "behaviors/soft-off",
      ],
    },
    {
      type: "category",
      label: "Codes",
      link: {
        type: "doc",
        id: "codes/index",
      },
      collapsed: true,
      items: [
        "codes/keyboard-keypad",
        "codes/modifiers",
        "codes/editing",
        "codes/media",
        "codes/applications",
        "codes/input-assist",
        "codes/power",
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
