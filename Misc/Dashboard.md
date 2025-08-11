# Dashboard

## Preface

대쉬 보드 UI를 위한 클래스

## Tips

- 각 페이지는 Canvas Panel로 구성되어 있지만 위젯 스위쳐로 인한 드로우 콜을 걱정하지 않아도 된다
    
    각 페이지가 활성화 될 때 한번씩만 드로우 되기 때문
    
- 버튼ui에 이미지를 넣는 방법은 버튼 자체 스타일을 변경하는 방법도 있지만
    
    overlay로 감싸서 image를 추가하는 방법도 있다: **Ovelay → Image, Button**
    

## Contents

- DashboardOverlay
    - GamePage
    - CareerPage
    - LeaderboardPage

- WBP_DashboardOverlay
    - WBP_GamePage
    - WBP_CareerPage
    - WBP_LeaderboardPage