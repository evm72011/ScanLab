import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import ScanLab 1.0 as SL

Item {
    id: root

    property var samples: []
    property int sampleCount: 512

    // диапазон сигнала
    property real minY: -1.0
    property real maxY:  1.0

    // mock animation
    property real phase: 0.0
    property bool animated: true
    property bool active: false

    Rectangle {
        anchors.fill: parent
        radius: 8
        color: SL.Theme.colors.windowBackground
        border.width: 1
        border.color: SL.Theme.colors.border
    }

    Canvas {
        id: canvas
        anchors.fill: parent
        anchors.margins: 8
        antialiasing: true

        onPaint: {
            const ctx = getContext("2d");
            ctx.reset();

            const w = width;
            const h = height;

            // background
            ctx.fillStyle = SL.Theme.colors.windowBackground;
            ctx.fillRect(0, 0, w, h);

            drawGrid(ctx, w, h);
            drawAxes(ctx, w, h);
            drawSignal(ctx, w, h);
        }

        function drawGrid(ctx, w, h) {
            ctx.save();
            ctx.strokeStyle = "rgba(255,255,255,0.10)";
            ctx.lineWidth = 1;

            const vSteps = 10;
            const hSteps = 8;

            for (let i = 0; i <= vSteps; ++i) {
                const x = i * w / vSteps;
                ctx.beginPath();
                ctx.moveTo(x, 0);
                ctx.lineTo(x, h);
                ctx.stroke();
            }

            for (let i = 0; i <= hSteps; ++i) {
                const y = i * h / hSteps;
                ctx.beginPath();
                ctx.moveTo(0, y);
                ctx.lineTo(w, y);
                ctx.stroke();
            }

            ctx.restore();
        }

        function drawAxes(ctx, w, h) {
            ctx.save();
            ctx.strokeStyle = "rgba(255,255,255,0.22)";
            ctx.lineWidth = 1;

            // baseline at y = 0
            const zeroY = mapY(0.0, h);
            ctx.beginPath();
            ctx.moveTo(0, zeroY);
            ctx.lineTo(w, zeroY);
            ctx.stroke();

            ctx.restore();
        }

        function drawSignal(ctx, w, h) {
            const data = root.samples;
            if (!data || data.length < 2)
                return;

            ctx.save();
            ctx.strokeStyle = "#6aa9ff";
            ctx.lineWidth = 1.5;
            ctx.beginPath();

            for (let i = 0; i < data.length; ++i) {
                const x = i * (w / (data.length - 1));
                const y = mapY(data[i], h);

                if (i === 0)
                    ctx.moveTo(x, y);
                else
                    ctx.lineTo(x, y);
            }

            ctx.stroke();
            ctx.restore();
        }

        function mapY(v, h) {
            const minV = root.minY;
            const maxV = root.maxY;
            const t = (v - minV) / (maxV - minV);
            return h * (1.0 - t);
        }
    }

    Timer {
        interval: 40
        running: root.animated && root.active
        repeat: true

        onTriggered: {
            root.phase += 0.18
            root.samples = createMockSamples(root.sampleCount, root.phase)
            canvas.requestPaint()
            console.log("A", root.phase);
        }
    }

    Component.onCompleted: {
        root.samples = createMockSamples(root.sampleCount, root.phase)
        canvas.requestPaint()
    }

    function createMockSamples(count, phase) {
        const result = []

        for (let i = 0; i < count; ++i) {
            const t = i / (count - 1)

            // базовый шум
            let y = 0.03 * (Math.random() - 0.5)

            // стартовый импульс
            y += pulse(t, 0.08, 0.010, 0.85)

            // 2 отражения
            y += pulse(t, 0.34, 0.018, 0.45 * (0.9 + 0.1 * Math.sin(phase)))
            y += pulse(t, 0.72, 0.025, 0.65 * (0.9 + 0.1 * Math.cos(phase * 0.7)))

            // легкая затухающая синусоида между отражениями
            y += 0.08 * Math.sin(60 * t + phase) * Math.exp(-3.2 * t)

            result.push(y)
        }

        return result
    }

    function pulse(t, center, width, amplitude) {
        const x = (t - center) / width
        return amplitude * Math.exp(-x * x) * Math.sin(18 * x)
    }
}
