#!/bin/bash
OUT=$1
shift
DS=""
for F in "$@"; do
  D=$(awk '{printf "{x:%s,y:%s},",$3,$1}' "$F")
  DS+="{label:'$F',data:[$D]},"
done

cat <<EOF > "$OUT"
<!DOCTYPE html>
<html>
<body>
<script src="https://cdn.jsdelivr.net/npm/chart.js"></script>
<canvas id="c"></canvas>
<script>
new Chart(document.getElementById('c'), {
  type: 'line',
  data: { datasets: [$DS] },
  options: {
    scales: {
      x: { type: 'logarithmic' },
      y: { type: 'logarithmic' }
    }
  }
});
</script>
</body>
</html>
EOF