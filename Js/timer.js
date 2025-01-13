console.time("timer_1")
for(let i=0; i < 10000; i++){
}
console.timeEnd("timer_1")

console.time("timer_2")
let i = 0;
while(i < 10000){
    i++
}
console.timeEnd("timer_2")