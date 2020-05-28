use crate::data::{CharacterTrait, Faction, ModeType};
use uuid::Uuid;

#[async_graphql::SimpleObject]
#[derive(Clone, Debug)]
pub struct AltMode {
    #[field(skip)]
    pub node_id: Uuid,

    pub id: i32,
    pub title: String,
    pub subtitle: String,
    pub stars: i32,
    pub type_: ModeType,
    pub faction: Faction,
    pub traits: Vec<CharacterTrait>,
    // Not available on Head or Upgrade modes
    pub health: i32,
    pub attack: i32,
    pub defense: i32,
}
