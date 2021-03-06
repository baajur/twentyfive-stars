module Fragment = [%relay.fragment
  {|
  fragment AllCards_query on QueryRoot
    @refetchable(queryName: "AllCardsRefetchQuery")
    @argumentDefinitions(
      count: { type: "Int", defaultValue: 20 }
      cursor: { type: "String", defaultValue: "" }
    ) {
    allCards(first: $count, after: $cursor)
      @connection(key: "AllCards_allCards") {
      edges {
        node {
          __typename
  
          ... on BattleCard {
            id
            ...BattleCard_battleCard
          }
          ... on CharacterCard {
            id
          }
        }
      }
    }
  }
|}
];

module Styles = {
  open Emotion;

  let cardList = [%css
    [
      display(grid),
      gridTemplateColumns(
        list([repeat(autoFill, [minmax(px(250), auto)])]),
      ),
      gridGap(rem(1.0)),
      // display(flexBox),
      // flexWrap(wrap),
    ]
  ];

  let placeholderCard = [%css []];

  let placeholderImage = [%css [minWidth(200->px), maxWidth(100.0->pct)]];
};

[@react.component]
let make = (~query as queryRef) => {
  let (isVisible, ref) = ReactIsVisible.useIsVisible();

  let ReasonRelay.{data, hasNext, isLoadingNext, loadNext} =
    Fragment.usePagination(queryRef);

  React.useEffect2(
    () =>
      if (isVisible && hasNext) {
        let d = loadNext(~count=10, ());
        Some(() => ReasonRelay.Disposable.dispose(d));
      } else {
        None;
      },
    (isVisible, hasNext),
  );

  let cards = data.allCards->Fragment.getConnectionNodes_allCards;

  let children =
    Belt.Array.map(cards, card => {
      switch (card) {
      | `BattleCard(card) =>
        <BattleCard key={card.id} card={card.getFragmentRefs()} />
      | _ => React.null
      }
    });

  <div className=Styles.cardList>
    {React.array(children)}
    <div className=Styles.placeholderCard key="loading-placeholder" ref>
      <div>
        <img
          className=Styles.placeholderImage
          src="https://tfsdb.netlify.com/images/card_back.png"
        />
      </div>
    </div>
  </div>;
};
