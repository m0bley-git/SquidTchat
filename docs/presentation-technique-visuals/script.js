const maxSteps = {
    "forum-flow": 3,
    "auth-sequence": 5,
    "stack-scene": 4,
    "broadcast-scene": 4,
};

const protocolExamples = {
    auth: {
        title: "auth/register",
        code: `{
  "type": "auth/register",
  "timestamp": "2026-04-04T15:00:00Z",
  "payload": {
    "pseudo": "Jean"
  }
}`,
    },
    forum: {
        title: "forum/send",
        code: `{
  "type": "forum/send",
  "timestamp": "2026-04-04T15:01:12Z",
  "payload": {
    "pseudo": "Jean",
    "content": "Salut à tous"
  }
}`,
    },
    mp: {
        title: "mp/send",
        code: `{
  "type": "mp/send",
  "timestamp": "2026-04-04T15:02:48Z",
  "payload": {
    "to": "Raphael",
    "content": "Tu peux verifier le serveur ?"
  }
}`,
    },
};

document.querySelectorAll("[data-cycle-target]").forEach((button) => {
    button.addEventListener("click", () => {
        const scene = document.querySelector(`[data-scene="${button.dataset.cycleTarget}"]`);
        if (!scene) return;

        const current = Number(scene.dataset.step || "0");
        const max = maxSteps[button.dataset.cycleTarget] ?? 0;
        scene.dataset.step = current >= max ? "1" : String(current + 1);
    });
});

document.querySelectorAll("[data-reset-target]").forEach((button) => {
    button.addEventListener("click", () => {
        const scene = document.querySelector(`[data-scene="${button.dataset.resetTarget}"]`);
        if (!scene) return;
        scene.dataset.step = "0";
    });
});

document.querySelectorAll(".protocol-switch").forEach((button) => {
    button.addEventListener("click", () => {
        const key = button.dataset.protocol;
        const example = protocolExamples[key];
        if (!example) return;

        document.getElementById("protocol-title").textContent = example.title;
        document.getElementById("protocol-code").textContent = example.code;

        document.querySelectorAll(".protocol-switch").forEach((item) => {
            item.classList.toggle("is-active", item === button);
            item.classList.toggle("mini-action--soft", item !== button);
        });
    });
});

document.getElementById("play-all")?.addEventListener("click", () => {
    const orderedScenes = ["forum-flow", "auth-sequence", "stack-scene", "broadcast-scene"];

    orderedScenes.forEach((sceneName, sceneIndex) => {
        const scene = document.querySelector(`[data-scene="${sceneName}"]`);
        if (!scene) return;

        scene.dataset.step = "0";
        const max = maxSteps[sceneName] ?? 0;

        for (let step = 1; step <= max; step += 1) {
            window.setTimeout(() => {
                scene.dataset.step = String(step);
            }, sceneIndex * 1600 + step * 340);
        }
    });
});
